// Zuzabr Games 2022 All Rights Reserved


#include "UI/GoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GM_MineSeeker.h"

void UGoToMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (GoToMenuButton)
	{
		GoToMenuButton->OnClicked.AddDynamic(this, &UGoToMenuWidget::OnGoToMenu);
	}
}

void UGoToMenuWidget::OnGoToMenu()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
	GameMode->OpenMainMenu();
}