// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MineSeekerCoreTypes.h"
#include "GI_MineSeeker.generated.h"

UCLASS()
class MINESEEKER_API UGI_MineSeeker : public UGameInstance
{
    GENERATED_BODY()

public:
    
    FOnOpenCellsSignature OnOpenCells;

    TArray<FCellData>* GetCellsData() { return &CellsData; }

    void SetGameSettings(const FMinesData& Settings) { GameSettings = Settings; }

    UFUNCTION(BlueprintCallable)
    FMinesData GetGameSettings() const { return GameSettings; }
    void CreateCellsData();
    void OpenCellsNearbyAutomatically(int32 ArrayIndex);
    void OpenCellsNearbyIntentionally(int32 ArrayIndex);

protected:
    TArray<FCellData> CellsData;
    TArray<int32> NearbyCellIndexes;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FMinesData GameSettings;

    void FillTheGrid();
    void SetMines();
    void CheckForMinesNearby();

    TArray<int32> GetNearbyCellIndexes(int32 ArrayIndex);
};
