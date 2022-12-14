// Zuzabr Games 2022 All Rights Reserved

#include "UI/CellWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Blueprint/WidgetTree.h"
#include "GI_MineSeeker.h"
#include "GM_MineSeeker.h"

void UCellWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    GameInstance = (GetWorld() != nullptr) ? GetWorld()->GetGameInstance<UGI_MineSeeker>() : nullptr;
}

FReply UCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

    if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
    {
        if (CellData->bClosed)
        {
            OnRightMouseClicked();
        }
    }

    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (CellData->bClosed)
        {
            OnLeftMouseClicked();
        }
    }

    return Reply;
}

FReply UCellWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
    FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
    if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
    {
        if (!CellData->bClosed)
        {
            OnLeftDoubleClick();
        }
    }

    return Reply;
}

void UCellWidget::OnLeftMouseClicked()
{
    if (ClosedCellSwitcher->ActiveWidgetIndex == 1) return;
    OpenTheCell(true);
}

void UCellWidget::OnRightMouseClicked()
{
    
    const auto ChildrenCount = ClosedCellSwitcher->GetChildrenCount();
    const auto CurrentIndex = ClosedCellSwitcher->ActiveWidgetIndex;

    if (CurrentIndex + 1 <= ChildrenCount - 1)
    {
        ClosedCellSwitcher->SetActiveWidgetIndex(CurrentIndex + 1);
        if ((CurrentIndex + 1) == 1)
        {
            CellData->MarkedAsMine = true;
            if (GameInstance)
            {
                GameInstance->ChangeRemainMinesCount(-1);
            }
        }
        else
        {
            CellData->MarkedAsMine = false;
            if (GameInstance)
            {
                GameInstance->ChangeRemainMinesCount(1);
            }
            
        }
    }
    else
    {
        ClosedCellSwitcher->SetActiveWidgetIndex(0);
        CellData->MarkedAsMine = false;
        
    }
}

void UCellWidget::OnLeftDoubleClick()
{
    if (!GameInstance) return;
    GameInstance->OpenCellsNearbyIntentionally(CellData->ArrayIndex);
}

void UCellWidget::SetCellData(FCellData* Data)
{
    CellData = Data;
    SetCellBackGround();
}


void UCellWidget::OpenTheCell(bool bCheckFlagSetup)
{
    // Happens only by user actions
    if (bCheckFlagSetup && !(ClosedCellSwitcher->ActiveWidgetIndex == 1))
    {
        CellData->bClosed = false; //Open cell in structure
        CellData->MarkedAsMine = false; //Remove flag from cell

        ClosedCellSwitcher->SetActiveWidget(0); // Hide Closed switcher
        ClosedCellSwitcher->SetVisibility(ESlateVisibility::Hidden);
        OpenEmptyCellsNearby();

        // Check on lost game
        if (CellData->bHasMine && GetWorld() && Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode()))
        {
            const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
            GameMode->GameLost();
        }

        // Check on win the game
        if (!(CellData->bHasMine) && GameInstance)
        {
            const auto bWin = GameInstance->CalculateOpenCellsNumber();
            if (bWin && GetWorld() && Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode())) 
            {
                const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
                GameMode->GameWon();
            }
        }
    }

    if (!bCheckFlagSetup)
    {
        CellData->bClosed = false;       // Open cell in structure
        CellData->MarkedAsMine = false;  // Remove flag from cell

        ClosedCellSwitcher->SetActiveWidget(0);  // Hide Closed switcher
        ClosedCellSwitcher->SetVisibility(ESlateVisibility::Hidden);
        OpenEmptyCellsNearby();
    }

    
}

bool UCellWidget::GetCellMineInfo() const
{
    return CellData->bHasMine;
}

void UCellWidget::OpenEmptyCellsNearby()
{
    if (!GameInstance) return;
    if (CellData->NumberOfNearMines == 0 && !CellData->bHasMine)
    {
        GameInstance->OpenCellsNearbyAutomatically(CellData->ArrayIndex);
    }
}

void UCellWidget::SetCellBackGround()
{
    if (CellData->bHasMine && OpenedCellImage)
    {
        OpenedCellImage->SetColorAndOpacity(FLinearColor::Red);

        return;
    }
    if (!(CellData->bHasMine) && CellData->NumberOfNearMines > 0 && NumberOfMinesNearby)
    {
        NumberOfMinesNearby->SetText(FText::AsNumber(CellData->NumberOfNearMines));
        NumberOfMinesNearby->SetVisibility(ESlateVisibility::Visible);
        return;
    }
    if (!(CellData->bHasMine) && (CellData->NumberOfNearMines == 0) && OpenedCellImage)
    {
        OpenedCellImage->SetColorAndOpacity(FLinearColor::White);
        return;
    }
}
