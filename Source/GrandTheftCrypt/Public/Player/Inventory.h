#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRANDTHEFTCRYPT_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	void AddItemToInventory(class AInventoryItem* InventoryItem);
	void RemoveFromInventory(FName item);

	UFUNCTION(BlueprintCallable)
	TArray<FName> GetInventory();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound configuration")
	class USoundBase* InventoryPickSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound configuration")
	class USoundAttenuation* SoundAttenuation;

	TArray<FName> Inventory;
};
