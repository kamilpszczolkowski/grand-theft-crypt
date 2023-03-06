#include "Player/Interact.h"
#include "Mover.h"
#include "Doors/Door.h"
#include "Player/Inventory.h"
#include "LeverTorch.h"
#include "InventoryItem.h"
#include "Player/PHandleComponent.h"
#include "CoreElements/GrandTheftCryptPlayerController.h"

#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

void UInteract::BeginPlay()
{
	Super::BeginPlay();

	Inventory = Cast<UInventory>(GetOwner()->GetComponentByClass(UInventory::StaticClass()));
	PhysicsHandle = Cast<UPHandleComponent>(GetOwner()->FindComponentByClass<UPhysicsHandleComponent>());
}

void UInteract::Grab()
{
	if (PhysicsHandle)
	{
		FHitResult HitResult;
		if(MakeSweepForObject(HitResult))
		{
			PhysicsHandle->Grab(HitResult);
		}
	}
}

void UInteract::Release()
{
	if(PhysicsHandle)
	{
		PhysicsHandle->Release();
	}
}

void UInteract::Interact()
{
	FHitResult HitResult;
	if(MakeSweepForObject(HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		if(HitActor->ActorHasTag(FName("DoorToOpen")))
		{
			ADoor* DoorsToOpen = Cast<ADoor>(HitActor);
			FName ValidKey;
			if(DoorsToOpen->TryToOpenDoor(Inventory->GetInventory(), ValidKey))
			{
				Inventory->RemoveFromInventory(ValidKey);
				AGrandTheftCryptPlayerController* PlayerController = 
					Cast<AGrandTheftCryptPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
				PlayerController->HideKeyWidget();
				const float KeyUsedTextDuration = 2.f;
				PlayerController->ShowTextWidget(FText::FromString("Key used"), KeyUsedTextDuration, ETextWidgetType::Secondary);
			}
		}
		else if(HitActor->ActorHasTag(FName("Inventory")))
		{
			AInventoryItem* InventoryItem = Cast<AInventoryItem>(HitActor);
			Inventory->AddItemToInventory(InventoryItem);
			InventoryItem->DestroyInventoryItem();
		}
		else if(HitActor->ActorHasTag(FName("Lever")))
		{
			ALeverTorch* Lever = Cast<ALeverTorch>(HitActor);
			Lever->ChangeLeverPosition();
		}
	}
}

bool UInteract::MakeSweepForObject(FHitResult &HitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxSweepDistance;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(SweepRadious);

	return GetWorld()->SweepSingleByChannel(
		HitResult, 
		Start, End, 
		FQuat::Identity, 
		ECC_GameTraceChannel2, 
		Sphere
	);
}
