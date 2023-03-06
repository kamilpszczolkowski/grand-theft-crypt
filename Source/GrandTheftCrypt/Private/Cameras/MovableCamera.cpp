#include "Cameras/MovableCamera.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Math/Color.h"


AMovableCamera::AMovableCamera()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;
}

void AMovableCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetActorLocation(FMath::VInterpTo(
        GetActorLocation(), 
        FinalPosition, 
        DeltaTime, 
        MoveSpeed 
    ));
}

void AMovableCamera::PossessAndMove()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if(PlayerController)
    {
        PlayerController->SetViewTargetWithBlend(this, BlendAmount);
    }
    SetActorTickEnabled(true);

    if(ShouldFadeIn)
    {
        APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
        if(CameraManager)
        {   
            CameraManager->StartCameraFade(1.f, 0.f, FadeInTime, FLinearColor::Black);
        }
    }
}
