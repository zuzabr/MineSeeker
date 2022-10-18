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


UCLASS()
class MINESEEKER_API UCellWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetCellData(const FCellData& Data);
	FCellData GetLvlData() const { return CellData; }

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* CellButton;

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
	void SetCellBackGround();
	
	FCellData CellData;

	
	
	
	
	
};
