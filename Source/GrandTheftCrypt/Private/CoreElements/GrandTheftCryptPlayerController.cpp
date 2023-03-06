#include "CoreElements/GrandTheftCryptPlayerController.h"
#include "UI/HUDWidget.h"
#include "UI/TextWidget.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AGrandTheftCryptPlayerController::ShowInstructionWidget(ETriggerType TriggerType)
{
    HideWidgetIfIsValid(InstructionWidgetInstance);
    InstructionWidgetInstance = CreateWidgetAndAddToViewport(TriggerType == ETriggerType::Grabber ? GrabWidget : InteractWidget);
}

void AGrandTheftCryptPlayerController::HideInstructionWidget()
{
    HideWidgetWithAnimationIfIsValid(InstructionWidgetInstance);
}

void AGrandTheftCryptPlayerController::ShowWidgetOnGameEnd(bool HasPlayerWon)
{
    if(DeathScreenWidget && WinScreenWidget)
    {
        CreateWidgetAndAddToViewport(HasPlayerWon ? WinScreenWidget : DeathScreenWidget);
    }
}

void AGrandTheftCryptPlayerController::ShowKeyWidget()
{
    if(KeyInInwentoryWidget)
    {
        KeyWidgetInstance = CreateWidgetAndAddToViewport(KeyInInwentoryWidget);
    }
}

void AGrandTheftCryptPlayerController::HideKeyWidget()
{
    HideWidgetIfIsValid(KeyWidgetInstance);
}

void AGrandTheftCryptPlayerController::ShowTextWidget(FText TextMessage, float DisplayDuration, ETextWidgetType MessageType)
{
    HideWidgetIfIsValid(TextWidgetInstance);
    if(GetWorldTimerManager().IsTimerActive(TextWidgetTimerHandle))
    {
        GetWorldTimerManager().ClearTimer(TextWidgetTimerHandle);
    }

    if(TextWidget)
    {
        TextWidgetInstance = CreateWidgetAndAddToViewport(TextWidget);
        if(MessageType == ETextWidgetType::Primary)
        {
            TextWidgetInstance->SetText(TextMessage);  
        }
        else if(MessageType == ETextWidgetType::Secondary)
        {
            TextWidgetInstance->SetSecondaryText(TextMessage);
        }

        GetWorldTimerManager().SetTimer(
            TextWidgetTimerHandle, 
            this, 
            &AGrandTheftCryptPlayerController::HideTextWidget, 
            DisplayDuration, 
            false
        );
    } 
}

void AGrandTheftCryptPlayerController::HideTextWidget()
{
    HideWidgetWithAnimationIfIsValid(TextWidgetInstance);
}

template<typename WidgetClass>
WidgetClass* AGrandTheftCryptPlayerController::CreateWidgetAndAddToViewport(
    TSubclassOf<WidgetClass> SpawnedWidgetClass)
{
	WidgetClass* SpawnedWidgetInstance = CreateWidget<WidgetClass>(GetWorld(), SpawnedWidgetClass);  
    if(SpawnedWidgetInstance)
    {
        SpawnedWidgetInstance->AddToViewport();
    }
    return SpawnedWidgetInstance;
}

template<typename WidgetClass>
void AGrandTheftCryptPlayerController::HideWidgetIfIsValid(WidgetClass* WidgetToHide)
{
    if(WidgetToHide)
    {
        WidgetToHide->RemoveFromViewport();
    }
}

template<typename WidgetClass>
void AGrandTheftCryptPlayerController::HideWidgetWithAnimationIfIsValid(WidgetClass* WidgetToHide)
{
    if(WidgetToHide)
    {
        WidgetToHide->DestroyWidgetWithAnimation();
    }
}
