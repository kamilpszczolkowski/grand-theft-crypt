#include "Doors/TwoWingsDoor.h"
#include "Triggers/InformationTriggerComponent.h"


ATwoWingsDoor::ATwoWingsDoor()
{
	PrimaryActorTick.bCanEverTick = true;

    DoorWay = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Doorway"));
    RootComponent = DoorWay;
    InformationTriggerComponent->SetupAttachment(DoorWay);

    LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left wing door"));
    LeftDoor->SetupAttachment(DoorWay);

    RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right wing door"));
    RightDoor->SetupAttachment(DoorWay);
}

void ATwoWingsDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(bDoorShouldOpen)
    {
        LeftDoor->SetRelativeRotation(
            FMath::RInterpConstantTo(
                LeftDoor->GetRelativeRotation(),
                LeftDoorTargetRotation,
                DeltaTime,
                DoorOpenSpeed
            )
        );  
        RightDoor->SetRelativeRotation(
            FMath::RInterpConstantTo(
                RightDoor->GetRelativeRotation(),
                RightDoorTargetRotation,
                DeltaTime,
                DoorOpenSpeed
            )
        );
    }
}
