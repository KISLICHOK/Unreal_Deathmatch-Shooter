// Shoot Them Up, All Rights Reserved


#include "STUGameInstance.h"
#include "Sound/STUSoundFuncLibrary.h"

void USTUGameInstance::ToggleVolume()
{
	USTUSoundFuncLibrary::ToggleSoundClassVolume(MasterSoundClass);
}
