#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GrandTheftCryptGameMode.generated.h"

UCLASS(minimalapi)
class AGrandTheftCryptGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWinCamera(AMovableCamera* Camera);
	UFUNCTION(BlueprintPure)
	bool ShouldSkipCameraSequence() const;

	void GameHadEnded(bool bIsGameWon);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound configuration")
	class USoundBase* HittingGroundSound;
	UPROPERTY(EditDefaultsOnly, Category = "Sound configuration")
	class USoundBase* WinSound;

	UPROPERTY()
	class AMovableCamera* WinCamera;

	void PlaySoundAndUnpossessCharacter(bool isGameWon);
	bool bSkipCameraSequence = false;
};
