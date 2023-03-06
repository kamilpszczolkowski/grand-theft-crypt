#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "InformationTriggerComponent.generated.h"

/*
Component is designed to provide instructions to a player who is standing near an 
interactable object and has been looking at it for some time wihtout taking any action. 
Correct widget will appear with instructions on how to interact with object. Additionaly
the owner of the component will start glowing (this component only implements delegate which 
is broadcasted at the right moment - glowing implementation is done on blueprint side).
*/

UENUM(BlueprintType)
enum class ETriggerType : uint8
{
	Grabber UMETA(DisplayName = "Grabber"),
	Interact UMETA(DisplayName = "Interact")
};

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStartElementGlow);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRANDTHEFTCRYPT_API UInformationTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()
	
public:
	UInformationTriggerComponent();
	virtual void TickComponent(
		float DeltaTime, 
		ELevelTick TickType, 
		FActorComponentTickFunction* ThisTickFunction
	) override;

    UPROPERTY(BlueprintAssignable)
    FOnStartElementGlow StartElementGlow;
	UPROPERTY(BlueprintAssignable)
    FOnStartElementGlow StopElementGlow;

	void RemoveInfoTrigger();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, category = "Grabber configuration")
	ETriggerType TriggerType = ETriggerType::Interact;

	UPROPERTY()
	class AGrandTheftCryptPlayerController* PlayerController;

	bool IsPlayerOverlappingTrigger() const;
	bool IsPlayerLookingAtOwner() const;
	void ShowInformation();
	void HideInformation();
	FTimerHandle InformationTimerHandle;
};
