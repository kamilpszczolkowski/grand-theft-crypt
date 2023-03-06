#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryItem.generated.h"

UCLASS()
class GRANDTHEFTCRYPT_API AInventoryItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AInventoryItem();
	FName GetInventoryItemName() const;
	void DestroyInventoryItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* InventoryMeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	class UInformationTriggerComponent* InformationTriggerComponent;

private:
	UPROPERTY(EditInstanceOnly, Category = "Item details")
	FName ItemName;
};
