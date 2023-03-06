#include "ChamberRiddle.h"
#include "LeverTorch.h"
#include "Mover.h"

#include "Kismet/GameplayStatics.h"

void AChamberRiddle::ChangePlayerRiddleSolution(int32 LeverNumber, bool bLeverState)
{
	if(!bLeverState)
	{
		ResetAllLevers();
	}
	else
	{
		PlayerRiddleSolution.Push(LeverNumber); 
		CheckSolution();
	}
}

void AChamberRiddle::ResetAllLevers()
{
	TArray<AActor*> Levers;
	UGameplayStatics::GetAllActorsOfClass(this, ALeverTorch::StaticClass(), Levers);

	for (AActor* Actor : Levers)
	{
		Cast<ALeverTorch>(Actor)->ResetLever();
	}

	PlayerRiddleSolution.Empty();

	for (UMover* Mover : PlatformsMoverComponents)
	{
		if(Mover)
		{
			Mover->SetIfObjectShouldMove(false);
		}
	}
}

void AChamberRiddle::CheckSolution()
{
	uint8 CurrentLeverNumber = 0;
	for(const int32 LeverNumber : PlayerRiddleSolution)
	{
		if(LeverNumber != CorrectRiddleSolution[CurrentLeverNumber])
		{
			ResetAllLevers();
			return;
		}
		CurrentLeverNumber++;
	}
	MovePlatforms();
}

void AChamberRiddle::MovePlatforms()
{
	/*This function moves a platform corresponding to the number of the latest lever that was pushed and added 
	to the solution. These platforms form a path towards the statues which the player needs to reach in order 
	to pass through the chamber.

	There are also two additional platforms stored under PlatformsMoverComponents with index 4 and 5 which lead 
	towards the player final destination and must be moved during the solution of the riddle. These are set to move 
	when PlatformsMoverComponents with index 1 and 3 is activated, respectively.*/

	UMover* MoverToControl = PlatformsMoverComponents[PlayerRiddleSolution.Num() -1];
	if(MoverToControl)
	{
		MoverToControl->SetIfObjectShouldMove(true);
	}

	if(PlayerRiddleSolution.Num() == 1)
	{
		PlatformsMoverComponents[5]->SetIfObjectShouldMove(true);
	}
	else if(PlayerRiddleSolution.Num() == 3)
	{
		PlatformsMoverComponents[4]->SetIfObjectShouldMove(true);
	}
}


void AChamberRiddle::SetMoverToPlatform(UMover* Mover, int PlatformNumber)
{
	PlatformsMoverComponents[PlatformNumber] = Mover;
}
