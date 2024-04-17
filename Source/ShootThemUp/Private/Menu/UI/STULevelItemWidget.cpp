// Shoot Them Up, All Rights Reserved


#include "Menu/UI/STULevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTULevelItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(LevelSelectButton)
	{
		LevelSelectButton->OnClicked.AddDynamic(this, &USTULevelItemWidget::OnLevelItemClick);
	}
}

void USTULevelItemWidget::OnLevelItemClick()
{
	OnLevelSelected.Broadcast(LevelData);
}

void USTULevelItemWidget::SetLevelData(const FLevelData& Data)
{
	LevelData = Data;
	if(LevelNameTextBlock)
	{
		LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
	}

	if(LevelImage)
	{
		LevelImage->SetBrushFromTexture(Data.LevelThumb);
	}
	
}

FLevelData USTULevelItemWidget::GetLevelData() const
{ return  LevelData; }

void USTULevelItemWidget::SetSelected(bool IsSelected)
{
	FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

