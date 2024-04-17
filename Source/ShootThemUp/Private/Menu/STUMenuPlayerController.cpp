// Shoot Them Up, All Rights Reserved


#include "Menu/STUMenuPlayerController.h"

#include "STUGameInstance.h"

void ASTUMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
	
}
