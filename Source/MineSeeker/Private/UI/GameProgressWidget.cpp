// Zuzabr Games 2022 All Rights Reserved


#include "UI/GameProgressWidget.h"
#include "GM_MineSeeker.h"
#include "Components/Button.h"

void UGameProgressWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
    if (PauseButton)
    {
        PauseButton->OnClicked.AddDynamic(this, &UGameProgressWidget::OnPauseSet);
    }

}

void UGameProgressWidget::OnPauseSet()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
    
    if (GameMode && GetOwningPlayer())
    {
        GameMode->SetPause(GetOwningPlayer());
    }
}
