#include "Doors/Door.h"
#include "Triggers/InformationTriggerComponent.h"

#include "Kismet/GameplayStatics.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;

    InformationTriggerComponent = CreateDefaultSubobject<UInformationTriggerComponent>(TEXT("Info Trigger"));
	InformationTriggerComponent->SetupAttachment(RootComponent);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	const float DoorOpeningAngle = 90.f;
    DoorOpenSpeed = DoorOpeningAngle / OpeningDuration;
}

bool ADoor::TryToOpenDoor(const TArray<FName>& Inventory, FName& OutValidKey)
{
    if(IsKeyPresentInInventory(Inventory))
    {
		OutValidKey = KeyToOpen;
		OpenDoor();
        return true;
    }
    else
    {
        if(DoorLockedSound && SoundAttenuation && !bDoorShouldOpen)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this, 
				DoorLockedSound, 
				GetActorLocation(), 
				FRotator::ZeroRotator, 
				1.f, 
				1.f, 
			    1.f, 
				SoundAttenuation
			);
	    }
        return false;
    }
}

bool ADoor::IsKeyPresentInInventory(const TArray<FName>& Inventory) const
{
	int32 inventoryIndex = Inventory.Find(KeyToOpen);
	return inventoryIndex != INDEX_NONE ? true : false;
}

void ADoor::OpenDoor()
{
	bDoorShouldOpen = true;
    this->SetActorTickEnabled(true);
    if(DoorOpeningSound && SoundAttenuation)
	{
		const float SoundFadeInTime = 0.8f;
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DoorOpeningSound,
			GetActorLocation(),
			FRotator::ZeroRotator,
			1.f,
			1.f,
			SoundFadeInTime,
			SoundAttenuation
		);
	}
	InformationTriggerComponent->RemoveInfoTrigger();
}
