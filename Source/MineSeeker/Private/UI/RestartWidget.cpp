// Zuzabr Games 2022 All Rights Reserved


#include "UI/RestartWidget.h"
#include "Components/Button.h"
#include "GM_MineSeeker.h"


void URestartWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &URestartWidget::RestartGame);
	}
}

void URestartWidget::RestartGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
	const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
	GameMode->StartGame();
}