#include "Triggers/InformationTriggerComponent.h"
#include "CoreElements/GrandTheftCryptPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"

UInformationTriggerComponent::UInformationTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UInformationTriggerComponent::BeginPlay()
{
    Super::BeginPlay();

    PlayerController = 
        Cast<AGrandTheftCryptPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UInformationTriggerComponent::TickComponent(
    float DeltaTime, 
    ELevelTick TickType, 
    FActorComponentTickFunction* ThisTickFunction
)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if(IsPlayerOverlappingTrigger())
    {
        if(IsPlayerLookingAtOwner())
        {
            if(!GetOwner()->GetWorldTimerManager().IsTimerActive(InformationTimerHandle))
            {
                const float ShowInfomrationDelay = 3.f;
                GetOwner()->GetWorldTimerManager().SetTimer(
                    InformationTimerHandle, 
                    this, 
                    &UInformationTriggerComponent::ShowInformation, 
                    ShowInfomrationDelay, 
                    false
                );
                StartElementGlow.Broadcast();
            }
        }
        else
        {
            HideInformation();  
        }
    }
    else
    { 
        HideInformation();
    }
}

bool UInformationTriggerComponent::IsPlayerOverlappingTrigger() const
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

    if(!OverlappingActors.IsEmpty())
    {
        for(AActor* Actor : OverlappingActors)
        {
            if(Actor == PlayerPawn)
            {
                return true;
            }
        }
    }
    return false;
}

bool UInformationTriggerComponent::IsPlayerLookingAtOwner() const
{
    /*Function takes result of FindLookAtRotation - which gives the angle between player and 
    Owner excluding Player current rotation. Exact angle between player and owner
    is calculated under const variables: YawRotationToOwnerFromLocationAndRotation and 
    PitchRotationToOwnerFromLocationAndRotation by subtracting current player rotation 
    and taking absolute value.*/

    FVector PlayerLocation;
    FRotator PlayerRotation;
    PlayerController->GetPlayerViewPoint(PlayerLocation, PlayerRotation);
    FRotator RotationToOwnerFromLocation = UKismetMathLibrary::FindLookAtRotation(
        PlayerLocation, 
        GetOwner()->GetActorLocation()
    );

    const double YawRotationToOwnerFromLocationAndRotation = 
        abs(RotationToOwnerFromLocation.Yaw - PlayerRotation.Yaw);
    const double PitchRotationToOwnerFromLocationAndRotation = 
        abs(RotationToOwnerFromLocation.Pitch - PlayerRotation.Pitch);

    const double AcceptableYawRotation = 70;
    const double AcceptablePitchRotation = 50;

    return (YawRotationToOwnerFromLocationAndRotation < AcceptableYawRotation) 
        && (PitchRotationToOwnerFromLocationAndRotation < AcceptablePitchRotation);
}

void UInformationTriggerComponent::ShowInformation()
{
    if(PlayerController != nullptr)
    {
        PlayerController->ShowInstructionWidget(TriggerType);
    }
}

void UInformationTriggerComponent::HideInformation()
{
    if(GetOwner()->GetWorldTimerManager().IsTimerActive(InformationTimerHandle))
    {
        GetOwner()->GetWorldTimerManager().ClearTimer(InformationTimerHandle);
        if(PlayerController)
        {
            PlayerController->HideInstructionWidget();
        }
        StopElementGlow.Broadcast();    
    }
}

void UInformationTriggerComponent::RemoveInfoTrigger()
{
    /*It's necessary to stop the timer from showing information Widget, otherwise it could still be 
    shown after this widget is destroyed.*/

    HideInformation();
    DestroyComponent(true);
}
