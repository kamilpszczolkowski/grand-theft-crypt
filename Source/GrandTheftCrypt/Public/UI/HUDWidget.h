#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/*
The widget declares a function that is used totrigger a fade-out animation and after it remove widget from parent.
Function definition is done on bleuprint side.
*/

UCLASS()
class GRANDTHEFTCRYPT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void DestroyWidgetWithAnimation();
};
