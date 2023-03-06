#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "TwoWingsDoor.generated.h"

UCLASS()
class GRANDTHEFTCRYPT_API ATwoWingsDoor : public ADoor
{
	GENERATED_BODY()
	
public:
	ATwoWingsDoor();
	virtual void Tick(float DeltaTime) override;

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	UStaticMeshComponent* DoorWay;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	UStaticMeshComponent* LeftDoor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Components")
	UStaticMeshComponent* RightDoor;

private:
	FRotator LeftDoorTargetRotation = FRotator(0.f, -180.f, 0.f);
    FRotator RightDoorTargetRotation = FRotator(0.f, 0.f, 0.f);
};
