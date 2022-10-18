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
//----------------------¬изуализаци€ массива €чеек----------------------------------------------------
	for (auto CellData : GameInstance->GetCellsData())
	{
		const auto CellWidget = CreateWidget<UCellWidget>(GetWorld(), CellWidgetClass);
		if (!CellWidget) continue;
		CellWidget->SetCellData(CellData);
		
		MinesGrid->AddChildToUniformGrid(CellWidget, CellData.CellRowIndex, CellData.CellColumnIndex);
		
		CellWidgets.Add(CellWidget);
	}
	SetFocus();
	
}

UGI_MineSeeker* UGridWidget::GetMineSeekerGI() const
{
	if (!GetWorld()) return nullptr;
	return GetWorld()->GetGameInstance<UGI_MineSeeker>();
}

void UGridWidget::OnFullGridUpdateNeeded(bool bNeeded)
{
	if (bNeeded == false) return;
	ResetFullMinesGrid();

}



