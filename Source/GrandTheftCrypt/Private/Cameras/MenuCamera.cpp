#include "Cameras/MenuCamera.h"

#include "Camera/CameraComponent.h"

void AMenuCamera::BeginPlay()
{
    Super::BeginPlay();

    Camera = GetCameraComponent();
    if(Camera)
    {
        Camera->PostProcessSettings.bOverride_DepthOfFieldFocalDistance = true;
        Camera->PostProcessSettings.DepthOfFieldFocalDistance = 1.f;
    }
}

void AMenuCamera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const float InterpolationSpeed = TargetDepthOfFieldFocalDistance / DepthOfFieldTransitionTime;
    if(Camera)
    {
        Camera->PostProcessSettings.DepthOfFieldFocalDistance = FMath::FInterpTo(
            Camera->PostProcessSettings.DepthOfFieldFocalDistance, 
            TargetDepthOfFieldFocalDistance,
            DeltaTime, 
            InterpolationSpeed
        );
    }
}
