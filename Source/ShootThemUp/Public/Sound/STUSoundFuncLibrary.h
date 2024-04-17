// Shoot Them Up, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STUSoundFuncLibrary.generated.h"

class USoundClass;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUSoundFuncLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	
	UFUNCTION(BlueprintCallable)
	static void ToggleSoundClassVolume(USoundClass* SoundClass);
	
};
