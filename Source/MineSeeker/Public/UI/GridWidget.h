// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
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

    void OnFullGridUpdateNeeded(bool bNeeded);
    void OnCellOpen(TArray<int32> ArrayIndex);
    void OnGameLost(EMatchState State);
};
