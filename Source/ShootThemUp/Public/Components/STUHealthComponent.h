// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCoreTypes.h"
#include "STUHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	USTUHealthComponent();

	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsDead() const { return FMath::IsNearlyZero(Health); }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	bool AutoHeal = true;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
		meta = (EditCondition = "AutoHeal", ClampMin = "0.001", ClampMax = "1000"))
	float HealUpdateTime = true;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
		meta = (EditCondition = "AutoHeal", ClampMin = "0.001", ClampMax = "1000"))
	float HealDelay = true;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
		meta = (EditCondition = "AutoHeal", ClampMin = "0.001", ClampMax = "1000"))
	float HealModifier = true;

	UPROPERTY(
		EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	TSubclassOf<UCameraShakeBase> CameraShake;

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

	bool TryToAddHealth(float HealthAmount);
	bool IsHealthFull() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0", ClampMax = "1000.0"))
	float MaxHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	TMap<TObjectPtr<UPhysicalMaterial>, float> DamageModifiers;

	virtual void BeginPlay() override;

private:
	float Health = 0.0f;
	FTimerHandle TimerHandle;

	UFUNCTION()
	void OnTakeAnyDamage(
		AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy,
		AActor* DamageCauser);

	UFUNCTION()
	void OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
	                       UPrimitiveComponent* FHitComponent, FName BoneName,
	                       FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser);

	UFUNCTION()
	void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin,
	                        const FHitResult& HitInfo, AController* InstigatedBy,
	                        AActor* DamageCauser);

	void HealUpdate();

	void SetHealth(float NewHealth);

	void PlayCameraShake();

	void Killed(AController* KillerController);

	void ApplyDamage(float Damage, AController* InstigatedBy);

	float GetPointDamageModifier(TObjectPtr<AActor> DamagedActor, const FName& BoneName);

	void ReportDamageEvent(float Damage, AController* InstigatedBy);
};
