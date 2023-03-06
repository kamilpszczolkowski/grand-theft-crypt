#include "InventoryItem.h"
#include "Triggers/InformationTriggerComponent.h"

AInventoryItem::AInventoryItem()
{
	InventoryMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Item mesh"));
	RootComponent = InventoryMeshComponent;
	InformationTriggerComponent = CreateDefaultSubobject<UInformationTriggerComponent>(TEXT("Info Trigger"));
	InformationTriggerComponent->SetupAttachment(InventoryMeshComponent);
}

FName AInventoryItem::GetInventoryItemName() const
{
	return ItemName;
}

void AInventoryItem::DestroyInventoryItem()
{
	InformationTriggerComponent->RemoveInfoTrigger();
	Destroy();
}
