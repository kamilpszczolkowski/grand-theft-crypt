#include "LeverTorch.h"

#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"

ALeverTorch::ALeverTorch()
{
	PrimaryActorTick.bCanEverTick = true;

	TorchComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Torch"));
	RootComponent = TorchComponent;

	FireParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Fire Particles"));
	FireParticlesComponent->SetupAttachment(TorchComponent);

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLightComponent->SetupAttachment(TorchComponent);
}

void ALeverTorch::BeginPlay()
{
	Super::BeginPlay();

	const float TorchBaseRollAngle = 15.f;

	StartRotation = GetActorRotation();
	StartRotation.Roll += TorchBaseRollAngle;

	TargetRotation = StartRotation;
	TargetRotation.Roll -= TorchRollAngleDelta;

	if(FireParticlesComponent)
	{
		FireParticlesComponent->Deactivate();
	}
}

void ALeverTorch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TorchRotationSpeed = TorchRollAngleDelta / RotationTime;
	const float PointLightIntensity = 2000.f;
	const float PointLightInterpSpeed = PointLightIntensity / RotationTime;

	TorchComponent->SetRelativeRotation(
		FMath::RInterpConstantTo(
			GetActorRotation(),
			bLeverState ? TargetRotation : StartRotation,
			DeltaTime,
			TorchRotationSpeed
		)
	);

	PointLightComponent->SetIntensity(
		FMath::FInterpConstantTo(
			PointLightComponent->Intensity,
			bLeverState ? PointLightIntensity : 0.f,
			DeltaTime,
			PointLightInterpSpeed
		)
	); 
}

void ALeverTorch::ChangeLeverPosition()
{		
	bLeverState = !bLeverState;
	bLeverState ? FireParticlesComponent->Activate() : FireParticlesComponent->Deactivate();

	if(LeverChangeSound && SoundAttenuation)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			LeverChangeSound, 
			GetActorLocation(), 
			FRotator::ZeroRotator, 
			1.f, 
			1.f, 
			0.f, 
			SoundAttenuation
		);
	}
	LeverPositionChange.Broadcast(LeverNumber, bLeverState);
}

void ALeverTorch::ResetLever()
{
	bLeverState = false;
	FireParticlesComponent->Deactivate();
}
