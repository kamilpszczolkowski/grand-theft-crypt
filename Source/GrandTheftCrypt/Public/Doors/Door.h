#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

/* Base class for door creation - door can be opened with correct key present in inventory.

Door will have it's position interpolated in tick function (children of this class). Tick starts
disabled as it's not necessary - activates when door should be opened.*/

UCLASS()
class GRANDTHEFTCRYPT_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoor();

	bool TryToOpenDoor(const TArray<FName>& Inventory, FName& OutValidKey);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	class UInformationTriggerComponent* InformationTriggerComponent;

	float DoorOpenSpeed;
	bool bDoorShouldOpen = false;

private:
	UPROPERTY(EditDefaultsOnly, category = "Open configuration")
	float OpeningDuration;
	UPROPERTY(EditDefaultsOnly, category = "Open configuration")
	class USoundBase* DoorOpeningSound;
	UPROPERTY(EditDefaultsOnly, category = "Open configuration")
	class USoundBase* DoorLockedSound;
	UPROPERTY(EditDefaultsOnly, category = "Open configuration")
	class USoundAttenuation* SoundAttenuation;
	UPROPERTY(EditInstanceOnly, category = "Open configuration")
	FName KeyToOpen;

	bool IsKeyPresentInInventory(const TArray<FName>& Inventory) const;
	void OpenDoor();
};
