#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "PHandleComponent.generated.h"

/*Physics Handle component is used to manage grabbing and releasing grabbable objects. Actor
needs to have the "Grabbable" tag in order for player to be able to grab it.

Grabbed items rotation is reset when grabbed (roll and pitch) in order for player to have it eassier 
to put the object in desired place without falling. */

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRANDTHEFTCRYPT_API UPHandleComponent : public UPhysicsHandleComponent
{
	GENERATED_BODY()

public:
	UPHandleComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Grab(const FHitResult& HitResult);
	void Release();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Grab configuration");
	float HoldDistance = 200.f;
	UPROPERTY(EditDefaultsOnly, Category = "Grab configuration");
	float PhysicsHandleLinearStiffness = 1500.f;
	UPROPERTY(EditDefaultsOnly, Category = "Grab configuration");
	float ComponentRotationResetSpeed = 400.f;
	UPROPERTY(EditDefaultsOnly, Category = "Grab configuration");
	FName ActorGrabbableTag = "Grabbable";

	bool bShouldRotationReset(FRotator GrabbedComponentRotaiton) const;
	void ResetRotation(FRotator GrabbedComponentRotaiton, float DeltaTime);

	bool bWasRotationAlreadyReset = true;
	const FName ActorGrabbedTag = "Grabbed";
};
