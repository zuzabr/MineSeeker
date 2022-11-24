// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MineSeekerCoreTypes.h"
#include "GM_MineSeeker.generated.h"

UCLASS()
class MINESEEKER_API AGM_MineSeeker : public AGameModeBase
{
    GENERATED_BODY()

public:
    AGM_MineSeeker();

    FOnMatchStateChangedSignature OnMatchStateChanged;
    FOnFullGridUpdateNeededSignature OnFullGridUpdateNeeded;
    

    virtual void StartPlay() override;
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    void OpenMainMenu();
    void StartGame();
    void GameLost();

private:
    EMatchState MatchState = EMatchState::None;
    void GameOver();
    void SetMatchState(EMatchState State);
};
