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
   
    UFUNCTION(BlueprintCallable)
    int32 GetMinesRemain() const { return MinesRemain; }

    UFUNCTION(BlueprintCallable)
    void SetGameSettings(int32 Columns, int32 Rows, int32 Bombs);
//****************************GameSttings**************************
    void SetColumns(int32 Columns) { GameSettings.ColumnsNumber = Columns; }
    void SetRows(int32 Rows) { GameSettings.RowsNumber = Rows; }
    void SetBombs(int32 Mines) { GameSettings.MinesNumber = Mines; }

    FORCEINLINE int32 GetColumns() const { return GameSettings.ColumnsNumber; }
    FORCEINLINE int32 GetRows() const { return GameSettings.RowsNumber; }
    
    UFUNCTION(BlueprintCallable)
    FORCEINLINE int32 GetBombs() const { return GameSettings.MinesNumber; }
//****************************GameSttings**************************
    UFUNCTION(BlueprintCallable)
    FMinesData GetGameSettings() const { return GameSettings; }
    void CreateCellsData();
    void OpenCellsNearbyAutomatically(int32 ArrayIndex);
    void OpenCellsNearbyIntentionally(int32 ArrayIndex);
    void ChangeRemainMinesCount(int32 Delta);
    bool CalculateOpenCellsNumber();

protected:
    TArray<FCellData> CellsData;
    TArray<int32> NearbyCellIndexes;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FMinesData GameSettings;

    void FillTheGrid();
    void SetMines();
    void CheckForMinesNearby();

    int32 NumberOfCellsToOpen{0};
    int32 OpenedCells{0};
    int32 MinesRemain{0};

    TArray<int32> GetNearbyCellIndexes(int32 ArrayIndex);

};
