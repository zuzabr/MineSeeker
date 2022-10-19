// Fill out your copyright notice in the Description page of Project Settings.

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
	
	TArray<FCellData> GetCellsData() const { return CellsData; }
	void SetGameSettings(const FMinesData& Settings) { GameSettings = Settings; }
	
	UFUNCTION(BlueprintCallable)
	FMinesData GetGameSettings() const { return GameSettings; }
	void CreateCellsData();
	void OpenCellsNearbyAutomatically(int32 ArrayIndex);
	void OpenCellsNearbyIntentionally(int32 ArrayIndex);
	void SetCellCloseStatus(int32 ArrayIndex, bool Closed);
	void SetCellFlagStatus(int32 ArrayIndex, bool Marked);

	

protected:
	
	
	TArray<int32> NearbyCellIndexes;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FMinesData GameSettings;
	
	void FillTheGrid();
	void SetMines();
	void CheckForMinesNearby();

	TArray<FCellData> CellsData;
	TArray<int32> GetNearbyCellIndexes(int32 ArrayIndex);


	
	
	
};
