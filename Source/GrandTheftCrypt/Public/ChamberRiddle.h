#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ChamberRiddle.generated.h"

/*The riddle consists of four levers and multiple moving platforms which will move to the correct position when 
the player activates the correct lever. The levers have to be activated in the correct order; if an incorrect 
lever is pushed, all the levers will reset to their base position and all the moving platforms will return 
to their initial position.

The torch lever is not illuminated when it's in the base position, but it becomes illuminated when it's in
the active position.

Every torch has a parameter which is torch number. These are stored in PlayerRiddleSolution when player pushes
the levers. Everytime player pushes the lever and solution is correct - platform which is stored in corresponding
index under PlatformsMoverComponents will be activated to move (there are two additional platforms which are activaded
during the activation of previus platforms in MovePlatforms function).

Moving platforms will form a path for the player towards two figures that have to be placed in the correct
positions to move the final platform. Two additional moving platforms will also form a path towards the entrance of the 
chamber that the player wants to exit.*/

UCLASS()
class GRANDTHEFTCRYPT_API AChamberRiddle : public AActor
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void ChangePlayerRiddleSolution(int32 LeverNumber, bool bLeverState);

	UFUNCTION(BlueprintCallable)
	void SetMoverToPlatform(UMover* Mover, int PlatformNumber);

private:
	TArray<int32> CorrectRiddleSolution = {1, 2, 3, 4};
	TArray<int32> PlayerRiddleSolution;
	TArray<class UMover*> PlatformsMoverComponents = {0, 0, 0, 0, 0, 0};

	void ResetAllLevers();
	void CheckSolution();
	void MovePlatforms();
};
