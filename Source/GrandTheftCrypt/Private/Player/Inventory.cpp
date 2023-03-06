#include "Player/Inventory.h"
#include "CoreElements/GrandTheftCryptPlayerController.h"
#include "InventoryItem.h"

#include "Kismet/GameplayStatics.h"

void UInventory::AddItemToInventory(class AInventoryItem* InventoryItem)
{
	Inventory.Add(InventoryItem->GetInventoryItemName());

	AGrandTheftCryptPlayerController* PlayerController = 
		Cast<AGrandTheftCryptPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	PlayerController->ShowKeyWidget();
	
	if(InventoryPickSound)
	{
		UGameplayStatics::PlaySound2D(this, InventoryPickSound);
	}

	const float ItemGrabbedTextDuration = 2.f;
	PlayerController->ShowTextWidget(
		FText::FromString("Item Grabbed"), 
		ItemGrabbedTextDuration, 
		ETextWidgetType::Secondary
	);
}

void UInventory::RemoveFromInventory(FName item)
{
	Inventory.Remove(item);
}

TArray<FName> UInventory::GetInventory()
{
	return Inventory;
}
