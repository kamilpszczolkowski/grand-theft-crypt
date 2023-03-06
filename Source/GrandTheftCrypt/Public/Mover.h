#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Mover.generated.h"

/*Component which can be attached to actors to make them move or/and rotate when specific condition happens.
Mover is controlled by TriggerComponent. Corresponding TriggerComponent has to be spawned somewhere on 
the map (mover is connected to specific trigger by calling TriggerComponent function in level blueprint). 
Trigger calls SetShouldMove function in the situation when trigger criteria are met or no longer met, therby
activating position interpolation realized in tick function of mover component.*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDTHEFTCRYPT_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMover();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetIfObjectShouldMove(bool bShouldObjectMove, bool bIsDoubleTrigger = false, bool bIsSecondTrigger = false);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	FVector MoveOffest;
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	FRotator RotationOffset;
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	float MoveTime = 4;
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	class USoundBase* MoveSound;
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	class USoundAttenuation* SoundAttenuation;

	class UAudioComponent* MoveSoundComponent;

	bool bIsObjectMoving = false;	
	bool bIsFirstTriggerActive = false;
	bool bIsSecondTriggerActive = false;

	FVector StartLocation;
	FVector TargetLocation;
	FRotator StartRotation;
	FRotator TargetRotation;

	float Speed;
	float RotationSpeed;
};
