#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Interact.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GRANDTHEFTCRYPT_API UInteract : public USceneComponent
{
	GENERATED_BODY()

public:	
	void Release();
	void Grab();
	void Interact();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sweep Configuration")
	float MaxSweepDistance = 400.f;

	UPROPERTY(EditDefaultsOnly, Category = "Sweep Configuration")
	float SweepRadious = 100.f;

	UPROPERTY()
	class UInventory* Inventory;
	UPROPERTY()
	class UPHandleComponent* PhysicsHandle;

	bool MakeSweepForObject(FHitResult &HitResult) const;
};
