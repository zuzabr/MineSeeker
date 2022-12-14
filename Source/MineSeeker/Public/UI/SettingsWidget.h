// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
#include "SettingsWidget.generated.h"

class UButton;
class USlider;
class UTextBlock;
class UGI_MineSeeker;

UCLASS()
class MINESEEKER_API USettingsWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* EasyButton;

    UPROPERTY(meta = (BindWidget))
    UButton* MediumButton;

    UPROPERTY(meta = (BindWidget))
    UButton* HardButton;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
    USlider* ColumnsSlider;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
    USlider* RowsSlider;

    UPROPERTY(meta = (BindWidget), BlueprintReadOnly)
    USlider* BombSlider;

    UPROPERTY(BlueprintReadOnly);
    int32 ColumnsNumber{10};
    UPROPERTY(BlueprintReadOnly);
    int32 RowsNumber{10};
    UPROPERTY(BlueprintReadOnly);
    int32 BombNumber{10};

     UGI_MineSeeker* GameInst;

private:

    UFUNCTION()
    void OnEasyChosen();

    UFUNCTION()
    void OnMediumChosen();

    UFUNCTION()
    void OnHardChosen();

    void SetMaxBombSliderLimit();

    UFUNCTION()
    void SetSettings(float Value=0.0f);

    UFUNCTION()
    void SetColumns(float Value);

    UFUNCTION()
    void SetRows(float Value);

    UFUNCTION()
    void SetBombs(float Value);

   
    
};
