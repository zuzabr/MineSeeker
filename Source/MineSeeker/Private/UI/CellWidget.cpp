// Zuzabr Games 2022 All Rights Reserved


#include "UI/CellWidget.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "GM_MineSeeker.h"


void UCellWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (CellButton)
	{
		CellButton->OnClicked.AddDynamic(this, &UCellWidget::OnLeftMouseClicked);
	}

	if (GetWorld())
	{
		const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnRightMouseClicked.AddUObject(this, &UCellWidget::OnRightMouseClicked);
		}
	}

	
		
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
	
	if (!CellButton->IsHovered() || !CellData.bClosed) return;
	UE_LOG(LogTemp, Warning, TEXT("Rigth Mouse Function worked"));
	const auto ChildrenCount = ClosedCellSwitcher->GetChildrenCount();
	UE_LOG(LogTemp, Warning, TEXT("Children Count %i"), ChildrenCount);
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