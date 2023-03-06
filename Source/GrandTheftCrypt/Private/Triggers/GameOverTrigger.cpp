#include "Triggers/GameOverTrigger.h"
#include "CoreElements/GrandTheftCryptGameMode.h"

#include "Kismet/GameplayStatics.h"

void UGameOverTrigger::BeginPlay()
{
    Super::BeginPlay();

    OnComponentBeginOverlap.AddDynamic(this, &UGameOverTrigger::OnOverlapBegin);
}

void UGameOverTrigger::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult
)
{
    if(OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
    {
        AGrandTheftCryptGameMode* GameMode = Cast<AGrandTheftCryptGameMode>(UGameplayStatics::GetGameMode(this));
        GameMode->GameHadEnded(bIsWinTrigger ? true : false);
    }
}
