// Zuzabr Games 2022 All Rights Reserved

#include "GM_MineSeeker.h"
#include "UI/MainHUD.h"
#include "SeekerController.h"

AGM_MineSeeker::AGM_MineSeeker()
{
    HUDClass = AMainHUD::StaticClass();
    PlayerControllerClass = ASeekerController::StaticClass();
}

void AGM_MineSeeker::SetMatchState(EMatchState State)
{
    if (MatchState == State) return;
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}

void AGM_MineSeeker::StartPlay()
{
    Super::StartPlay();
    OpenMainMenu();
}

void AGM_MineSeeker::OpenMainMenu()
{
    SetMatchState(EMatchState::WaitingToStart);
}

void AGM_MineSeeker::StartGame()
{
    if (IsPaused())
    {
        ClearPause();
    }

    OnFullGridUpdateNeeded.Broadcast(true);
    SetMatchState(EMatchState::InProgress);
}

void AGM_MineSeeker::GameOver()
{
    SetMatchState(EMatchState::GameOver);
}

bool AGM_MineSeeker::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(EMatchState::Pause);
    }
    return PauseSet;
}

bool AGM_MineSeeker::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EMatchState::InProgress);
    }

    return PauseCleared;
}

void AGM_MineSeeker::GameLost()
{
    if (MatchState == EMatchState::GameOver) return;
    SetMatchState(EMatchState::GameOver);
}