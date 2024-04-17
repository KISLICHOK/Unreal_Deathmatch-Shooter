// Shoot Them Up, All Rights Reserved


#include "Menu/UI/STUMenuWidget.h"

#include "STUGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/STULevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUMenuWidget, All, All)

void USTUMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnStartGame);
	}

	if(QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMenuWidget::OnQuitGame);
	}

	InitLevelItems();
}

void USTUMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if(Animation != HideAnimation) return;
	if(!GetWorld()) return;
	const auto STUGameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();

	UGameplayStatics::OpenLevel(this, STUGameInstance->GetStartupLevel().LevelName);
}

void USTUMenuWidget::OnStartGame()
{
	PlayAnimation(HideAnimation);
	UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTUMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMenuWidget::InitLevelItems()
{
	const auto STUGameInstance = GetStuGameInstance();
    if(!STUGameInstance) return;

	checkf(STUGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

	if(!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

	for(auto LevelData : STUGameInstance->GetLevelsData())
	{
		const auto LevelItemWidget = CreateWidget<USTULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
		if(!LevelItemWidget) continue;

		LevelItemWidget->SetLevelData(LevelData);
		LevelItemWidget->OnLevelSelected.AddUObject(this, &USTUMenuWidget::OnLevelSelected);

		LevelItemsBox->AddChild(LevelItemWidget);
		LevelItemWidgets.Add(LevelItemWidget);
	}

	if(STUGameInstance->GetStartupLevel().LevelName.IsNone())
	{
		OnLevelSelected(STUGameInstance->GetLevelsData()[0]);
	}else
	{
		OnLevelSelected(STUGameInstance->GetStartupLevel());
	}
}

void USTUMenuWidget::OnLevelSelected(const FLevelData& Data)
{
	const auto STUGameInstance = GetStuGameInstance();
	if(!STUGameInstance) return;

	STUGameInstance->SetStartupLevel(Data);

	for(auto LevelItemWidget : LevelItemWidgets)
	{
		if(LevelItemWidget)
		{
			const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;

			LevelItemWidget->SetSelected(IsSelected);
		}
	}
}

USTUGameInstance* USTUMenuWidget::GetStuGameInstance() const
{
	if(!GetWorld()) return nullptr;

	return GetWorld()->GetGameInstance<USTUGameInstance>();
}