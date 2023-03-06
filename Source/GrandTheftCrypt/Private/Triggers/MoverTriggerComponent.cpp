#include "Triggers/MoverTriggerComponent.h"
#include "Mover.h"

UMoverTriggerComponent::UMoverTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMoverTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!ControlledMoverComponent) return;

    if(bIsTriggerActive())
    {
        ControlledMoverComponent->SetIfObjectShouldMove(true, isDoubleTrigger, isSecondTrigger);
        if(!bWasTriggerArleadyActivated)
        {
            bWasTriggerArleadyActivated = true;
            TriggerActivatedFirstTIme.Broadcast();
        }
    }
    else
    {
        ControlledMoverComponent->SetIfObjectShouldMove(false, isDoubleTrigger, isSecondTrigger);
    }
}

void UMoverTriggerComponent::SetMoverToControl(UMover* NewMover)
{
    ControlledMoverComponent = NewMover;
}

bool UMoverTriggerComponent::bIsTriggerActive() const
{
    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);
    for(AActor* Actor : Actors)
    {
        bool bActorHasUnlockTag = CheckIfActorHasTag(Actor, ActorUnlockTag);
        bool bActorHasGrabbedTag = CheckIfActorHasTag(Actor, ActorGrabbedTag);

        if (bActorHasUnlockTag && !bActorHasGrabbedTag)
        {
            return true;
        }
    }
    return false;
}

bool UMoverTriggerComponent::CheckIfActorHasTag(AActor* actor, FName tag) const
{
    return actor->ActorHasTag(tag);
}

