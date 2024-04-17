// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUMenuWidget.generated.h"

class UHorizontalBox;
class UButton;
class USTUGameInstance;
class USTULevelItemWidget;
class USoundCue;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMenuWidget : public USTUBaseWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> LevelItemsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> LevelItemWidgetClass;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	TObjectPtr<UWidgetAnimation> HideAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<USoundCue> StartGameSound;
	
	virtual void NativeOnInitialized() override;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UPROPERTY()
	TArray<TObjectPtr<USTULevelItemWidget>> LevelItemWidgets;
	
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

	void InitLevelItems();
	void OnLevelSelected(const FLevelData& Data);
	USTUGameInstance* GetStuGameInstance() const;
};
