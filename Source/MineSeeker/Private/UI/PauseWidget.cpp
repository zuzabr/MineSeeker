// Zuzabr Games 2022 All Rights Reserved


#include "UI/PauseWidget.h"
#include "GM_MineSeeker.h"
#include "Components/Button.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (ClearPauseButton)
	{
		ClearPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClearPause);
	}


}

void UPauseWidget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->ClearPause();
	}
}
