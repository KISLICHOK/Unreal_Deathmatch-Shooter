// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STULevelItemWidget.generated.h"

class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTULevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FOnLevelSelectedSignature OnLevelSelected;

	void SetLevelData(const FLevelData& Data);
	FLevelData GetLevelData() const;

	void SetSelected(bool IsSelected);
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LevelImage = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> FrameImage;

	virtual void NativeOnInitialized() override;

private:
	FLevelData LevelData;

	UFUNCTION()
	void OnLevelItemClick();
};
