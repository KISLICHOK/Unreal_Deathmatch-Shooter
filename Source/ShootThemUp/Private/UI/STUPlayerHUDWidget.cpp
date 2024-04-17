// Shoot Them Up, All Rights Reserved


#include "UI/STUPlayerHUDWidget.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUWeaponComponent.h"
#include "STUUtils.h"
#include "Components/ProgressBar.h"

void USTUPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if(GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    
}

void USTUPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(NewPawn);
    if (IsValid(HealthComponent) && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}


float USTUPlayerHUDWidget::GetHealthPercent() const
{

    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    if (!IsValid(HealthComponent)) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!IsValid(WeaponComponent)) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTUPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(GetOwningPlayerPawn());
    if (!IsValid(WeaponComponent)) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}


bool USTUPlayerHUDWidget::IsPlayerAllive() const
{
    const auto HealthComponent = STUUtils::GetSTUPlayerComponent<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}



void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if(HealthDelta < 0)
    {
        OnTakeDamage();

        if(!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    UpdateHealthBar();
}

int32 USTUPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if(!Controller) return 0;

    const auto PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString USTUPlayerHUDWidget::FormatBullets(int32 BulletNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';
    auto BulletStr = FString::FromInt(BulletNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();
    if(SymbolsNumToAdd > 0)
    {
        BulletStr = FString::ChrN(SymbolsNumToAdd,PrefixSymbol).Append(BulletStr);
    }
    return BulletStr;
}

void USTUPlayerHUDWidget::UpdateHealthBar()
{
    if(IsValid(HealthProgressBar))
    {
        HealthProgressBar->SetFillColorAndOpacity(GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
}
