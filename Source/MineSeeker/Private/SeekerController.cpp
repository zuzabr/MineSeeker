// Zuzabr Games 2022 All Rights Reserved


#include "SeekerController.h"
#include "Gameframework/GameModeBase.h"
#include "GM_MineSeeker.h"

void ASeekerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	
	bShowMouseCursor = true;
	
}

void ASeekerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (!InputComponent) return;


	InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASeekerController::OnPauseGame);
	InputComponent->BindAction("RightMouseClick", IE_DoubleClick, this, &ASeekerController::OnRMBClicked);	
	
}

void ASeekerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->SetPause(this);
}

void ASeekerController::OnRMBClicked()
{
	const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;
	GameMode->ClickRMB();
}