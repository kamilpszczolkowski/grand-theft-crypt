#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
#include "TextWidget.generated.h"

/*Widget created to display texts on the screen bound to the bleuprint widget which
defines it's appearance.*/

UCLASS()
class GRANDTHEFTCRYPT_API UTextWidget : public UHUDWidget
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TextBlock;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* SecondaryTextBlock;

	void SetText(FText TextMessage);
	void SetSecondaryText(FText TextMessage);
};
