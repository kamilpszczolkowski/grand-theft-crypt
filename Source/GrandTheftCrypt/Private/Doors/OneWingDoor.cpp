#include "Doors/OneWingDoor.h"
#include "Triggers/InformationTriggerComponent.h"

AOneWingDoor::AOneWingDoor()
{
    Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
    RootComponent = Door;
    InformationTriggerComponent->SetupAttachment(Door);
}

void AOneWingDoor::BeginPlay()
{
    Super::BeginPlay();

    TargetRotation = GetActorRotation();
    
    const float DoorOpenAngle = 90.f;
    TargetRotation.Yaw -= DoorOpenAngle;
}

void AOneWingDoor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if(bDoorShouldOpen)
    {
        Door->SetRelativeRotation(
            FMath::RInterpConstantTo(
                GetActorRotation(),
                TargetRotation,
                DeltaTime,
                DoorOpenSpeed
            )
        );
    }
}
