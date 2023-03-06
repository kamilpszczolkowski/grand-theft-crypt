#include "CoreElements/GrandTheftCryptCharacter.h"
#include "Player/Interact.h"

#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "TimerManager.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

AGrandTheftCryptCharacter::AGrandTheftCryptCharacter() : TurnRateGamepad(34.f)
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
 	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	InteractComponent = CreateDefaultSubobject<UInteract>(TEXT("Interact component"));
	InteractComponent->SetupAttachment(FirstPersonCameraComponent);
}

void AGrandTheftCryptCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAction("Grab", IE_Pressed, InteractComponent, &UInteract::Grab);
	PlayerInputComponent->BindAction("Grab", IE_Released, InteractComponent, &UInteract::Release);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, InteractComponent, &UInteract::Interact);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &AGrandTheftCryptCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &AGrandTheftCryptCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &AGrandTheftCryptCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &AGrandTheftCryptCharacter::LookUpAtRate);
}

void AGrandTheftCryptCharacter::MoveForward(float Value)
{
	CheckPlayerVelocityAndPlaySound();
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AGrandTheftCryptCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AGrandTheftCryptCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGrandTheftCryptCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void AGrandTheftCryptCharacter::CheckPlayerVelocityAndPlaySound()
{
	/*
	Function plays step sounds when player velocity in X or Y direction is different than 0).
	Audo is stopped when Z velocity is different than 0 (when player is jumping/falling).	
	*/

	FVector PlayerVelocity = GetVelocity();
	const double VelocityDetectionThreshold = 2;

	bool bPlayerHasVelocityX = abs(PlayerVelocity.X) > VelocityDetectionThreshold;
	bool bPlayerHasVelocityY = abs(PlayerVelocity.Y) > VelocityDetectionThreshold;
	bool bPlayerHasVelocityZ = (PlayerVelocity.Z == 0);

	if((bPlayerHasVelocityX || bPlayerHasVelocityY) && bPlayerHasVelocityZ)
	{
		if(!GetWorldTimerManager().IsTimerActive(StepsTimerHandle))
		{
			GetWorldTimerManager().SetTimer(StepsTimerHandle, this, &AGrandTheftCryptCharacter::PlayStepSound, 0.5f, true);
		}
	}
	else
	{
		if(GetWorldTimerManager().IsTimerActive(StepsTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(StepsTimerHandle);
		}
	}
}

void AGrandTheftCryptCharacter::PlayStepSound()
{
	UGameplayStatics::PlaySoundAtLocation(this, FootSteps, GetActorLocation(), 0.4f);
}

void AGrandTheftCryptCharacter::HandleGameOver()
{
	if(GetWorldTimerManager().IsTimerActive(StepsTimerHandle))
	{
		GetWorldTimerManager().ClearTimer(StepsTimerHandle);
	}
	UGameplayStatics::GetPlayerController(this, 0)->UnPossess();
}
