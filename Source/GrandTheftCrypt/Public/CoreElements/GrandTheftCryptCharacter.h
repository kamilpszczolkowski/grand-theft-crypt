#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GrandTheftCryptCharacter.generated.h"

/*
Character class was automatically created by unreal engine and is a little bit different
due to that fact in terms of code formatting - should still be refactored.
*/

class UInputComponent;
class USceneComponent;
class UCameraComponent;
class USoundBase;

UCLASS(config=Game)
class AGrandTheftCryptCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	AGrandTheftCryptCharacter();

	void HandleGameOver();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

protected:
	void MoveForward(float Val);
	void MoveRight(float Val);
	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);
	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UInteract* InteractComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Walking")
	class USoundBase* FootSteps;
	
	void CheckPlayerVelocityAndPlaySound();
	void PlayStepSound();

	FTimerHandle StepsTimerHandle;
};
