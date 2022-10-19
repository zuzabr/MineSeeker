// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GridWidget.h"
#include "Components/UniformGridPanel.h"
#include "GI_MineSeeker.h"
#include "GM_MineSeeker.h"
#include "UI/CellWidget.h"



void UGridWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

//----------------------ѕодписываемс€ на делегат---------------------------------------------
	if (GetWorld())
	{
		const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnFullGridUpdateNeeded.AddUObject(this, &UGridWidget::OnFullGridUpdateNeeded);
		}
			
	}	

	const auto GameInstance = GetMineSeekerGI();
	if (GameInstance)
	{
		GameInstance->OnOpenCells.AddUObject(this, &UGridWidget::OnCellOpen);
	}
			
}

void UGridWidget::ResetFullMinesGrid()
{
	const auto GameInstance = GetMineSeekerGI();
	if (!GameInstance) return;

//------------------------—оздаем массив €чеек----------------------------------------------------
	GameInstance->CreateCellsData();

	checkf(GameInstance->GetCellsData().Num() != 0, TEXT("Cells data must not be empty!"));

	if (!MinesGrid) return;
	MinesGrid->ClearChildren();
	const auto Data = GameInstance->GetCellsData();

//----------------------¬изуализаци€ массива €чеек----------------------------------------------------
	for (auto& CellData : GameInstance->GetCellsData())
	{
		const auto CellWidget = CreateWidget<UCellWidget>(GetWorld(), CellWidgetClass);
		if (!CellWidget) continue;
		CellWidget->SetCellData(CellData);
		
		MinesGrid->AddChildToUniformGrid(CellWidget, CellData.CellRowIndex, CellData.CellColumnIndex);
		
		CellWidgets.Add(CellWidget);
	}
	SetFocus();

	
	
}


void UGridWidget::OnFullGridUpdateNeeded(bool bNeeded)
{
	if (bNeeded == false) return;
	ResetFullMinesGrid();

}

void UGridWidget::OnCellOpen(TArray<int32> ArrayIndex)
{
	for (int32& Index : ArrayIndex)
	{
		const auto Cell = Cast<UCellWidget>(MinesGrid->GetChildAt(Index));
		if (!(Cell->GetCellData().bClosed)) continue;
		Cell->OpenTheCell();
	}
	
}

UGI_MineSeeker* UGridWidget::GetMineSeekerGI() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UGI_MineSeeker>();
}
