// Shoot Them Up, All Rights Reserved


#include "UI/STUStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void USTUStatRowWidget::SetPlayerName(const FText& Text)
{
	if(!PlayerNameTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUStatRowWidget::SetKills(const FText& Text)
{
	if(!KillsTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUStatRowWidget::SetDeaths(const FText& Text)
{
	if(!DeathsTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUStatRowWidget::SetTeam(const FText& Text)
{
	if(!TeamTextBlock) return;
	PlayerNameTextBlock->SetText(Text);
}

void USTUStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
	if(!PlayerIndicatorImage) return;
	PlayerNameTextBlock->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUStatRowWidget::SetTeamColor(const FLinearColor& Color)
{
	if(!IsValid(TeamImage)) return;
	TeamImage->SetColorAndOpacity(Color);
}
