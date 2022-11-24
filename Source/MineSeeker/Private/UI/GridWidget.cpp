// Zuzabr Games 2022 All Rights Reserved

#include "UI/GridWidget.h"
#include "Components/UniformGridPanel.h"
#include "GI_MineSeeker.h"
#include "GM_MineSeeker.h"
#include "UI/CellWidget.h"

void UGridWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnFullGridUpdateNeeded.AddUObject(this, &UGridWidget::OnFullGridUpdateNeeded);
            GameMode->OnMatchStateChanged.AddUObject(this, &UGridWidget::OnGameLost);
        }
    }

    const auto GameInstance = GetMineSeekerGI();
    if (GameInstance)
    {
        GameInstance->OnOpenCells.AddUObject(this, &UGridWidget::OnCellOpen);
    }
}
//--------------------------------Create new game field----------------------------------
void UGridWidget::ResetFullMinesGrid()
{
    const auto GameInstance = GetMineSeekerGI();
    if (!GameInstance) return;

    GameInstance->CreateCellsData();

    if (!MinesGrid || !CellWidgetClass || !GetWorld()) return;
    MinesGrid->ClearChildren();
    auto Data = GameInstance->GetCellsData();
    
    for (auto& CellData : *Data)
    {
        auto CellWidget = CreateWidget<UCellWidget>(GetWorld(), CellWidgetClass);
        if (!CellWidget) continue;
        CellWidget->SetCellData(&CellData);

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

//----------------------Open needed array of cells-------------------------------------
void UGridWidget::OnCellOpen(TArray<int32> ArrayIndex)
{
    for (int32& Index : ArrayIndex)
    {
        const auto Cell = Cast<UCellWidget>(MinesGrid->GetChildAt(Index));
        if (!(Cell->GetCellData()->bClosed)) continue;
        Cell->OpenTheCell();
    }
}

UGI_MineSeeker* UGridWidget::GetMineSeekerGI() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UGI_MineSeeker>();
}

void UGridWidget::OnGameLost(EMatchState State) 
{
    if (State != EMatchState::GameOver) return;
    
    const auto GameInstance = GetMineSeekerGI();
    if (!GameInstance) return;

    const int32 ArrayLength = GameInstance->GetCellsData()->Num();

    for (int32 i =0;i<ArrayLength; ++i)
    {
        const auto Cell = Cast<UCellWidget>(MinesGrid->GetChildAt(i));
        if (!(Cell->GetCellData()->bClosed)) continue;
        Cell->OpenTheCell();
    }
}