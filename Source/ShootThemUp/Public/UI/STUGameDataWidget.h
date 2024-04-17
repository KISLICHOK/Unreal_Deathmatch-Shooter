// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

class ASTUPlayerState;
class ASTUGameModeBase;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category ="UI")
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable, Category ="UI")
	int32 GetTotalRoundNum() const;

	UFUNCTION(BlueprintCallable, Category ="UI")
	int32 GetRoundSecondsRemaining() const;

private:
	ASTUGameModeBase* GetSTUGameModeBase() const;
	ASTUPlayerState* GetSTUPlayerState() const;
};
