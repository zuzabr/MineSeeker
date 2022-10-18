// Zuzabr Games 2022 All Rights Reserved


#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GM_MineSeeker.h"

void UMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnStartGame);
	}

	if (QuitGameButton)
	{
		QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnQuitGame);
	}
	
}

void UMainMenuWidget::OnStartGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
	GameMode->StartGame();
}



void UMainMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

