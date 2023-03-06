#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "MoverTriggerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggeredFirstTimeSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDTHEFTCRYPT_API UMoverTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UMoverTriggerComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void SetMoverToControl(UMover* Mover);

	UPROPERTY(BlueprintAssignable)
	FTriggeredFirstTimeSignature TriggerActivatedFirstTIme;

private:
	UPROPERTY(EditInstanceOnly, Category = "Trigger configuration")
	FName ActorUnlockTag; 
	UPROPERTY(EditInstanceOnly, Category = "Trigger configuration")
	bool isDoubleTrigger = false;
	UPROPERTY(EditInstanceOnly, Category = "Trigger configuration")
	bool isSecondTrigger = false;

	UPROPERTY()
	class UMover* ControlledMoverComponent;

	bool bIsTriggerActive() const;
	bool CheckIfActorHasTag(AActor* actor, FName tag) const;
	bool bWasTriggerArleadyActivated = false;
	const FName ActorGrabbedTag = "Grabbed";
};
