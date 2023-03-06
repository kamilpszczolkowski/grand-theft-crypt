#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Triggers/InformationTriggerComponent.h"

#include "GrandTheftCryptPlayerController.generated.h"

UENUM(BlueprintType)
enum class ETextWidgetType : uint8
{
	Primary UMETA(DisplayName = "Primary"),
	Secondary UMETA(DisplayName = "Secondary")
};

UCLASS()
class GRANDTHEFTCRYPT_API AGrandTheftCryptPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	void ShowInstructionWidget(ETriggerType TriggerType);
	void HideInstructionWidget();
	void ShowWidgetOnGameEnd(bool HasPlayerWon);
	void ShowKeyWidget();
	void HideKeyWidget();
	
	UFUNCTION(BlueprintCallable)
	void ShowTextWidget(
		FText TextMessage, 
		float DisplayDuration = 5.f, 
		ETextWidgetType MessageType = ETextWidgetType::Primary
	);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UHUDWidget> InteractWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UHUDWidget> GrabWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> DeathScreenWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> WinScreenWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UUserWidget> KeyInInwentoryWidget;
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
	TSubclassOf<class UTextWidget> TextWidget;

	UPROPERTY()
	class UHUDWidget* InstructionWidgetInstance;
	UPROPERTY()
	class UUserWidget* KeyWidgetInstance;
	UPROPERTY()
	class UTextWidget* TextWidgetInstance;

	void HideTextWidget();

	template<typename WidgetClass>
	WidgetClass* CreateWidgetAndAddToViewport(TSubclassOf<WidgetClass> SpawnedWidgetClass);
	template<typename WidgetClass>
	void HideWidgetIfIsValid(WidgetClass* WidgetToHide);
	template<typename WidgetClass>
	void HideWidgetWithAnimationIfIsValid(WidgetClass* WidgetToHide);
	FTimerHandle TextWidgetTimerHandle;
};
