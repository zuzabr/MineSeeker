// Zuzabr Games 2022 All Rights Reserved


#include "UI/CellWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GM_MineSeeker.h"
#include "Blueprint/WidgetTree.h"


void UCellWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (CellButton)
	{
		CellButton->OnClicked.AddDynamic(this, &UCellWidget::OnLeftMouseClicked);
	}

}


FReply UCellWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Right mouse was pressed"));
		OnRightMouseClicked();	
	}

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Left mouse was pressed"));
		OnRightMouseClicked();
	}

	return Reply;
}

FReply UCellWidget::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDoubleClick(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UE_LOG(LogTemp, Warning, TEXT("Double left mouse was pressed"));
	}

	return Reply;
}

void UCellWidget::OnLeftMouseClicked()
{
	if (ClosedCellSwitcher->ActiveWidgetIndex == 1) return;
	CellData.bClosed = false;
	CellButton->SetVisibility(ESlateVisibility::Hidden);
}

void UCellWidget::SetCellData(const FCellData& Data)
{
	CellData = Data;
	CellData.bClosed = true;
	SetCellBackGround();
}

void UCellWidget::OnRightMouseClicked()
{
	
	if (!CellData.bClosed) return;
	
	const auto ChildrenCount = ClosedCellSwitcher->GetChildrenCount();
	const auto CurrentIndex = ClosedCellSwitcher->ActiveWidgetIndex;
	
	if (CurrentIndex + 1 <= ChildrenCount - 1)
	{
		ClosedCellSwitcher->SetActiveWidgetIndex(CurrentIndex + 1);
	}
	else
	{
		ClosedCellSwitcher->SetActiveWidgetIndex(0);
	}
	
}

void UCellWidget::SetCellBackGround()
{
	if (CellData.bHasMine && OpenedCellImage)
	{
		OpenedCellImage->SetColorAndOpacity(FLinearColor::Red);
		
		return;
	}
	if (CellData.NumberOfNearMines > 0 && NumberOfMinesNearby)
	{
		NumberOfMinesNearby->SetText(FText::AsNumber(CellData.NumberOfNearMines));
		NumberOfMinesNearby->SetVisibility(ESlateVisibility::Visible);
		return;
	}
	if (CellData.NumberOfNearMines == 0 && OpenedCellImage)
	{
		OpenedCellImage->SetColorAndOpacity(FLinearColor::Blue);
		return;
	}
}

