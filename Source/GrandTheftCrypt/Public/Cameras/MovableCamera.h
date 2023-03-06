#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "MovableCamera.generated.h"

/*Camera moving from one position to another in specified time. Starts with Tick function disabled,
when movement should start - tick function is enabled.*/

UCLASS()
class GRANDTHEFTCRYPT_API AMovableCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:	
	AMovableCamera();

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void PossessAndMove();

private:
	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	FVector FinalPosition;

	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	float MoveSpeed = 1.f;

	UPROPERTY(EditInstanceOnly, Category = "Movement configuration")
	float BlendAmount = 0.f;

	UPROPERTY(EditInstanceOnly, Category = "Fade configuration")
	bool ShouldFadeIn = true;

	UPROPERTY(EditInstanceOnly, Category = "Fade configuration")
	float FadeInTime;
};
