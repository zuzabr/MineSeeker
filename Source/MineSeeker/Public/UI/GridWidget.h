// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GridWidget.generated.h"

class UUniformGridPanel;
class UGI_MineSeeker;
class UCellWidget;

UCLASS()
class MINESEEKER_API UGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	void ResetFullMinesGrid();

protected:
	UPROPERTY(meta = (BindWidget))
		UUniformGridPanel* MinesGrid;

	UPROPERTY(EditdefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> CellWidgetClass;

private:
	UGI_MineSeeker* GetMineSeekerGI() const;

	UPROPERTY()
		TArray<UCellWidget*> CellWidgets;

	void OnFullGridUpdateNeeded(bool bNeeded); // Создаем функцию под делегат
	
			
};
