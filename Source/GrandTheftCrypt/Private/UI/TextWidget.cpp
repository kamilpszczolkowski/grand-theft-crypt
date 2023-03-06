#include "UI/TextWidget.h"

#include "Components/TextBlock.h"

void UTextWidget::SetText(FText TextMessage)
{
    if(TextBlock)
    {
        TextBlock->SetText(TextMessage);
    }
}

void UTextWidget::SetSecondaryText(FText TextMessage)
{
    if(SecondaryTextBlock)
    {
        SecondaryTextBlock->SetText(TextMessage);
    }
}
