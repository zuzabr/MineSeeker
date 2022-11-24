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
    OpenTheCell();
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
            // GameInstance->SetCellFlagStatus(CellData.ArrayIndex, true);
        }
        else
        {
            CellData->MarkedAsMine = false;
            // GameInstance->SetCellFlagStatus(CellData.ArrayIndex, false);
        }
    }
    else
    {
        ClosedCellSwitcher->SetActiveWidgetIndex(0);
        CellData->MarkedAsMine = false;
        // GameInstance->SetCellFlagStatus(CellData.ArrayIndex, false);
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

void UCellWidget::OpenTheCell()
{
    if (!(ClosedCellSwitcher->ActiveWidgetIndex == 1))
    {
        CellData->bClosed = false;
        CellData->MarkedAsMine = false;

        if (CellData->bHasMine && GetWorld() && Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode()))
        {
            const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
            GameMode->GameLost();
        }

        ClosedCellSwitcher->SetActiveWidget(0);
        ClosedCellSwitcher->SetVisibility(ESlateVisibility::Hidden);
        OpenEmptyCellsNearby();
    }
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
    if (CellData->NumberOfNearMines > 0 && NumberOfMinesNearby)
    {
        NumberOfMinesNearby->SetText(FText::AsNumber(CellData->NumberOfNearMines));
        NumberOfMinesNearby->SetVisibility(ESlateVisibility::Visible);
        return;
    }
    if (CellData->NumberOfNearMines == 0 && OpenedCellImage)
    {
        OpenedCellImage->SetColorAndOpacity(FLinearColor::White);
        return;
    }
}
