// Shoot Them Up, All Rights Reserved

#include "Player/STUPlayerController.h"

#include "STUGameInstance.h"
#include "STUGameModeBase.h"
#include "STURespawnComponent.h"
#include "GameFramework/GameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld())
	{
		if (const auto GameMode = Cast<ASTUGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->OnMatchStateChange.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
		}
	}
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(!InputComponent) return;

	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTUPlayerController::OnPauseGame);
	InputComponent->BindAction("Mute", IE_Pressed, this, &ASTUPlayerController::OnMuteSound);
}


void ASTUPlayerController::OnPauseGame()
{
	if(!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::InProgress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}

void ASTUPlayerController::OnMuteSound()
{
	if(!GetWorld()) return;
	const auto STUGameInstace = GetWorld()->GetGameInstance<USTUGameInstance>();

	STUGameInstace->ToggleVolume();
}
