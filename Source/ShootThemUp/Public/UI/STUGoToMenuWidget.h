// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGoToMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> GoToMenuButton;
	
	virtual void NativeOnInitialized() override;
	
private:
	UFUNCTION()
	void OnGoToMenu();
};
