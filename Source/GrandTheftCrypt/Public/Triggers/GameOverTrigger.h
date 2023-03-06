#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameOverTrigger.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRANDTHEFTCRYPT_API UGameOverTrigger : public UBoxComponent
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComponent, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex,
		bool bFromSweep, 
		const FHitResult& SweepResult
	);

	UPROPERTY(EditInstanceOnly, Category = "Trigger type")
	bool bIsWinTrigger = false;
};
