// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "STUCoreTypes.h"
#include "GameFramework/HUD.h"
#include "STUGameHUD.generated.h"

class USTUBaseWidget;
class USTUPlayerHUDWidget;

UCLASS()
class SHOOTTHEMUP_API ASTUGameHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void DrawHUD() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;


private:
    UPROPERTY()
    TMap<ESTUMatchState, TObjectPtr<USTUBaseWidget>> GameWidgets;

    UPROPERTY()
     TObjectPtr<USTUBaseWidget> CurrentWidget = nullptr;
    
    void DrawCrossHair();

    void OnMatchStateChanged(ESTUMatchState State);
};
