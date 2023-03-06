#include "Player/PHandleComponent.h"
#include "Player/Interact.h"
#include "Triggers/InformationTriggerComponent.h"

UPHandleComponent::UPHandleComponent()
{
    PrimaryComponentTick.bCanEverTick = true;  
    LinearStiffness = PhysicsHandleLinearStiffness;
}

void UPHandleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    UInteract* InteractComponent = Cast<UInteract>(GetOwner()->FindComponentByClass(UInteract::StaticClass()));

    if(GrabbedComponent)
    {
		FRotator GrabbedComponentRotaiton = GrabbedComponent->GetComponentRotation();
		FVector TargetLocation = InteractComponent->GetComponentLocation() 
			+ InteractComponent->GetForwardVector() * HoldDistance;

        GrabbedComponent->WakeAllRigidBodies();

        if(bShouldRotationReset(GrabbedComponentRotaiton))
		{
			ResetRotation(GrabbedComponentRotaiton, DeltaTime);
			SetTargetLocation(TargetLocation);
		} 
		else
		{
			bWasRotationAlreadyReset = true;
			SetTargetLocationAndRotation(TargetLocation, InteractComponent->GetComponentRotation());
		}
   }
}

void UPHandleComponent::Grab(const FHitResult& HitResult)
{
    UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	AActor* HitActor = HitResult.GetActor();

	if(HitActor->ActorHasTag(ActorGrabbableTag))
	{
		HitComponent->WakeAllRigidBodies();
		HitComponent->SetSimulatePhysics(true);
		HitComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		HitActor->Tags.Add(ActorGrabbedTag);
		bWasRotationAlreadyReset = false;

		GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitResult.ImpactPoint,
			HitComponent->GetComponentRotation()
		);

		//Removing information trigger - it should not prompt the player when action was already taken
		UInformationTriggerComponent* InformationTriggerComponent = 
			Cast<UInformationTriggerComponent>(HitActor->GetComponentByClass(UInformationTriggerComponent::StaticClass()));
		if(InformationTriggerComponent)
		{
			InformationTriggerComponent->RemoveInfoTrigger();
		}
	}
}

void UPHandleComponent::Release()
{
    if(GrabbedComponent)
	{
		AActor* GrabbedActor = GrabbedComponent->GetOwner();
		GrabbedActor->Tags.Remove(ActorGrabbedTag);
		GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		ReleaseComponent();
	}
}

bool UPHandleComponent::bShouldRotationReset(FRotator GrabbedComponentRotaiton) const
{
	return static_cast<int>(GrabbedComponentRotaiton.Pitch + GrabbedComponentRotaiton.Roll) != 0 
		&& ! bWasRotationAlreadyReset;
}

void UPHandleComponent::ResetRotation(FRotator GrabbedComponentRotaiton, float DeltaTime)
{
	FRotator GrabbedComponentTargetRotation = FRotator(0.f, GrabbedComponentRotaiton.Yaw, 0.f);
	GrabbedComponent->SetWorldRotation(
		FMath::RInterpConstantTo(
			GrabbedComponentRotaiton,
			GrabbedComponentTargetRotation,
			DeltaTime,
			ComponentRotationResetSpeed
		)
	);
}
