// Shoot Them Up, All Rights Reserved


#include "Components/STUAIWeaponComponent.h"

void USTUAIWeaponComponent::StartFire()
{
	if(!CanFire()) return;

	if(CurentWeapon->IsAmmoEmpty())
	{
		NextWeapon();
	}
	else
	{
		CurentWeapon->StartFire();
	}
}

void USTUAIWeaponComponent::NextWeapon()
{
	if(!CanEquip()) return;
	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

	while(NextIndex != CurrentWeaponIndex)
	{
		if(!Weapons[NextIndex]->IsAmmoEmpty()) break;
		NextIndex = (NextIndex + 1) % Weapons.Num();
	}

	if(CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
