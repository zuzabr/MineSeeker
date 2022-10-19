// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
#include "CellWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
class UWidgetSwitcher;
class UGI_MineSeeker;

UCLASS()
class MINESEEKER_API UCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetCellData(const FCellData &Data);
	FCellData GetCellData() const { return CellData; }
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void OpenTheCell();

	virtual void NativeOnInitialized() override;
	
protected:	
	
	UPROPERTY(meta = (BindWidget))
		UWidgetSwitcher* ClosedCellSwitcher;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* NumberOfMinesNearby;

	UPROPERTY(meta = (BindWidget))
		UImage* ClosedEmptyCellImage;

	UPROPERTY(meta = (BindWidget))
		UImage* ClosedQuestionCellImage;

	UPROPERTY(meta = (BindWidget))
		UImage* ClosedFlagCellImage;
	
	UPROPERTY(meta = (BindWidget))
		UImage* OpenedCellImage;

private:
	UFUNCTION(BlueprintCallable)

	void OnLeftMouseClicked();
	void OnRightMouseClicked();
	void OnLeftDoubleClick();
	void OpenEmptyCellsNearby();
	void SetCellBackGround();
	
	void GetMineSeekerGI();
	UGI_MineSeeker *GameInstance;

	FCellData CellData;
						
};
