#include "Mover.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "TimerManager.h"

#include <algorithm>

UMover::UMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	TargetLocation = StartLocation + MoveOffest;
	Speed = FVector::Dist(StartLocation, TargetLocation) / MoveTime;

	StartRotation = GetOwner()->GetActorRotation();
	TargetRotation = StartRotation + RotationOffset;

	//The biggest rotation value is taken to calculate rotation speed as it will take the longest to rotate in that axis.
	float MaxRotationValue = std::max({RotationOffset.Yaw, RotationOffset.Pitch, RotationOffset.Roll});
	RotationSpeed = MaxRotationValue / MoveTime;
}

void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetOwner()->SetActorLocation(
		FMath::VInterpConstantTo(
			GetOwner()->GetActorLocation(), 
			bIsObjectMoving ? TargetLocation : StartLocation, 
			DeltaTime, 
			Speed
		)
	);

	GetOwner()->SetActorRotation(
		FMath::RInterpConstantTo(
			GetOwner()->GetActorRotation(),
			bIsObjectMoving ? TargetRotation : StartRotation,
			DeltaTime,
			RotationSpeed
		)
	);
}

void UMover::SetIfObjectShouldMove(bool bShouldObjectMove, bool bIsDoubleTrigger, bool bIsSecondTrigger)
{
	/*This funciton checks whether the mover is controlled by two triggers or one, based on that 
	it sets bShouldObjectMove directly or one of the trigger statuses. In case of double trigger 
	platform starts moving when both triggers are active.*/

	bool bWasPlatformMoving = bIsObjectMoving;
	if(bIsDoubleTrigger)
	{
		if(bIsSecondTrigger)
		{
			bIsSecondTriggerActive = bShouldObjectMove;
		}
		else
		{
			bIsFirstTriggerActive = bShouldObjectMove;
		}

		bIsObjectMoving = bIsFirstTriggerActive && bIsSecondTriggerActive;
	}
	else
	{
		bIsObjectMoving = bShouldObjectMove;
	}

	if(bWasPlatformMoving != bIsObjectMoving)
	{
		if(MoveSound && SoundAttenuation)
		{
			MoveSoundComponent = UGameplayStatics::SpawnSoundAtLocation(
				this, 
				MoveSound, 
				GetOwner()->GetActorLocation(), 
				FRotator::ZeroRotator, 
				1.f, 
				1.f, 
				0.f,
				SoundAttenuation
			);	
		}
	}
}
