#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "OneWingDoor.generated.h"

UCLASS()
class GRANDTHEFTCRYPT_API AOneWingDoor : public ADoor
{
	GENERATED_BODY()
public:
	AOneWingDoor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	UStaticMeshComponent* Door;

private:
	FRotator TargetRotation;
};
