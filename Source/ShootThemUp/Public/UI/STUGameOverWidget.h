// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUBaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "STUCoreTypes.h"
#include "STUGameOverWidget.generated.h"

class UButton;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public USTUBaseWidget
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* PlayerStatBox;

	UPROPERTY(meta=(BindWidget))
	UButton* ResetLevelButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

	virtual void NativeOnInitialized() override;

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdatePlayersStat();

	UFUNCTION()
	void OnResetLevel();
};
