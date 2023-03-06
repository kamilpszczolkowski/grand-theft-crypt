#pragma once

#include "CoreMinimal.h"
#include "MovableCamera.h"
#include "MenuCamera.generated.h"

/*Camera with utility of interpolated Depth of field focal distance.*/

UCLASS()
class GRANDTHEFTCRYPT_API AMenuCamera : public AMovableCamera
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Camera parameters")
	float TargetDepthOfFieldFocalDistance = 20.f;
	UPROPERTY(EditDefaultsOnly, Category = "Camera parameters")
	float DepthOfFieldTransitionTime = 10.f;

	UPROPERTY()
	class UCameraComponent* Camera;
};
