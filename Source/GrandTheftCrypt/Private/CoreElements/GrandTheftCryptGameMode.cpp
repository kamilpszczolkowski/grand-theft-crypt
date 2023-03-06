#include "CoreElements/GrandTheftCryptGameMode.h"
#include "CoreElements/GrandTheftCryptCharacter.h"
#include "CoreElements/GrandTheftCryptPlayerController.h"
#include "Cameras/MovableCamera.h"

#include "Kismet/GameplayStatics.h"
#include "Sound/AmbientSound.h"

void AGrandTheftCryptGameMode::GameHadEnded(bool bIsGameWon)
{
	bSkipCameraSequence = bIsGameWon ? false : true;

	TArray<AActor*> AmbientSounds;
	UGameplayStatics::GetAllActorsOfClass(this, AAmbientSound::StaticClass(), AmbientSounds);
	for(AActor* Actor : AmbientSounds)
	{
		Cast<AAmbientSound>(Actor)->FadeOut(1.f, 0.f);
	}

	AGrandTheftCryptPlayerController* PlayerController = 
		Cast<AGrandTheftCryptPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if(PlayerController)
	{
		PlayerController->ShowWidgetOnGameEnd(bIsGameWon);
	}

	if(bIsGameWon)
	{
		if(WinCamera) WinCamera->PossessAndMove();
	}

	FTimerHandle GameOverTimerHandle;
	FTimerDelegate GameOverTimerDelegate = FTimerDelegate::CreateUObject(
		this,
		&AGrandTheftCryptGameMode::PlaySoundAndUnpossessCharacter,
		bIsGameWon
	);
	const float GameOverTimerWinDelay = 3.f;
	const float GmaeOverTimerLoseDelay = 1.f;
	GetWorldTimerManager().SetTimer(
		GameOverTimerHandle, 
		GameOverTimerDelegate, 
		bIsGameWon ? GameOverTimerWinDelay : GmaeOverTimerLoseDelay, 
		false
	);
}

void AGrandTheftCryptGameMode::PlaySoundAndUnpossessCharacter(bool bIsGameWon)
{
	if(WinSound && HittingGroundSound)
	{
		UGameplayStatics::PlaySound2D(this, bIsGameWon ? WinSound : HittingGroundSound);
	}
	AGrandTheftCryptCharacter* PlayerCharacter = 
		Cast<AGrandTheftCryptCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if(PlayerCharacter)
	{
		PlayerCharacter->HandleGameOver();
	}
}

void AGrandTheftCryptGameMode::SetWinCamera(AMovableCamera* Camera)
{
	WinCamera = Camera;
}

bool AGrandTheftCryptGameMode::ShouldSkipCameraSequence() const
{
	return bSkipCameraSequence;
}
