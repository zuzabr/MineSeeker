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
	UFUNCTION(BlueprintCallable)
	TArray<FCellData> GetCellsData() const { return  CellsData; }
	void SetGameSettings(const FMinesData& Settings) { GameSettings = Settings; }
	FMinesData GetGameSettings() const { return GameSettings; }
	void CreateCellsData();

protected:
	
	TArray<FCellData> CellsData;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FMinesData GameSettings;

	void FillTheGrid();
	void SetMines();
	void CheckForMinesNearby();

//--------Временно--------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FCellData CellData;
	
};
