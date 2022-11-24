// Zuzabr Games 2022 All Rights Reserved

#include "UI/MainHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "GM_MineSeeker.h"

void AMainHUD::BeginPlay()
{
    Super::BeginPlay();
       
    GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), GameProgressWidgetClass));
    GameWidgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
    GameWidgets.Add(EMatchState::WaitingToStart, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
    GameWidgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));   
    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;

        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GetWorld())
    {
        const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &AMainHUD::OnMatchStateChanged);
        }
    }
}

void AMainHUD::OnMatchStateChanged(EMatchState State)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWidget = GameWidgets[State];
    }

    if (State == EMatchState::GameOver && GameWidgets.Contains(EMatchState::InProgress))
    {
        GameWidgets[EMatchState::InProgress]->SetVisibility(ESlateVisibility::Visible);
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

}