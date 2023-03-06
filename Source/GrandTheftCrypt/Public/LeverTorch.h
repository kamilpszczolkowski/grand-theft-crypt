#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LeverTorch.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLeverPositionChanged, int32, LeverNumber, bool, LeverState);

UCLASS()
class GRANDTHEFTCRYPT_API ALeverTorch : public AActor
{
	GENERATED_BODY()
	
public:	
	ALeverTorch();
	virtual void Tick(float DeltaTime) override;

	void ChangeLeverPosition(); 
	void ResetLever();

	UPROPERTY(BlueprintAssignable)
    FOnLeverPositionChanged LeverPositionChange;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* TorchComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UParticleSystemComponent* FireParticlesComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	class UPointLightComponent* PointLightComponent;
	UPROPERTY(EditDefaultsOnly, Category = "Lever configuration")
	class USoundBase* LeverChangeSound;
	UPROPERTY(EditDefaultsOnly, Category = "Lever configuration")
	class USoundAttenuation* SoundAttenuation;
	UPROPERTY(EditInstanceOnly, Category = "Lever configuration")
	int32 LeverNumber;
	UPROPERTY(EditDefaultsOnly, Category = "Lever configuration")
	float RotationTime = 1.f;

	FRotator StartRotation;
	FRotator TargetRotation;
	bool bLeverState = false;
	const float TorchRollAngleDelta = 30.f;
};
