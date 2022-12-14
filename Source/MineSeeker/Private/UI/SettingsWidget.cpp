// Zuzabr Games 2022 All Rights Reserved


#include "UI/SettingsWidget.h"
#include "Components/Slider.h"
#include "Components/Button.h"
#include "GI_MineSeeker.h"

void USettingsWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

//***********************************ButtonsBinding**************************
    if (EasyButton)
    {
        EasyButton->OnClicked.AddDynamic(this, &USettingsWidget::OnEasyChosen);
    }
    if (MediumButton)
    {
        MediumButton->OnClicked.AddDynamic(this, &USettingsWidget::OnMediumChosen);
    }
    if (HardButton)
    {
        HardButton->OnClicked.AddDynamic(this, &USettingsWidget::OnHardChosen);
    }

//**********************SetDefaultSettings*********************************
    if (GetWorld())
    {
        GameInst = GetWorld()->GetGameInstance<UGI_MineSeeker>();
    }
    if (GameInst)
    {
        ColumnsNumber = GameInst->GetColumns();
        RowsNumber = GameInst->GetRows();
        BombNumber = GameInst->GetBombs();
    }
    
    if (ColumnsSlider)
    {
        ColumnsSlider->SetMinValue(9);
        ColumnsSlider->SetMaxValue(30);
        ColumnsSlider->SetValue(ColumnsNumber);
        ColumnsSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetColumns);
        
    }
    if (RowsSlider)
    {
        RowsSlider->SetMinValue(9);
        RowsSlider->SetMaxValue(24);
        RowsSlider->SetValue(RowsNumber);
        RowsSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetRows);
    }
    if (BombSlider)
    {
        BombSlider->SetMinValue(9);
        SetMaxBombSliderLimit();
        BombSlider->SetValue(BombNumber);
        BombSlider->OnValueChanged.AddDynamic(this, &USettingsWidget::SetBombs);
    }
  
}

//*****************OnButtonClicked*******************************
void USettingsWidget::OnEasyChosen()
{
    ColumnsSlider->SetValue(9);
    RowsSlider->SetValue(9);
    BombSlider->SetValue(10);
    SetSettings();
   
}

void USettingsWidget::OnMediumChosen()
{
    ColumnsSlider->SetValue(16);
    RowsSlider->SetValue(16);
    BombSlider->SetValue(40);
    SetSettings();
    
}

void USettingsWidget::OnHardChosen()
{
    ColumnsSlider->SetValue(30);
    RowsSlider->SetValue(16);
    BombSlider->SetValue(99);
    SetSettings();
    
}

void USettingsWidget::SetMaxBombSliderLimit() 
{
    int32 Value = (ColumnsNumber*RowsNumber) / 3;    
    BombSlider->SetMaxValue(Value);

    if (BombNumber > Value)
    {
        BombSlider->SetValue(Value);
        BombNumber = Value;
        if (GameInst)
        {
            GameInst->SetBombs(Value);
        }
    }
}

void USettingsWidget::SetSettings(float Value)
{
    
    ColumnsNumber = ColumnsSlider->Value;
    RowsNumber = RowsSlider->Value;
    BombNumber = BombSlider->Value;

    SetMaxBombSliderLimit();
    
    if (!GameInst) return;
    GameInst->SetGameSettings(ColumnsSlider->Value, RowsSlider->Value, BombSlider->Value);
    
}

void USettingsWidget::SetColumns(float Value)
{
   
    ColumnsNumber = Value;
    SetMaxBombSliderLimit();
    
    if (!GameInst) return;
    GameInst->SetColumns(Value);
}

void USettingsWidget::SetRows(float Value)
{
    RowsNumber = Value;
    SetMaxBombSliderLimit();

    if (!GameInst) return;
    GameInst->SetRows(Value);
}

void USettingsWidget::SetBombs(float Value)
{
    BombNumber = Value;
    SetMaxBombSliderLimit();

    if (!GameInst) return;
    GameInst->SetBombs(Value);
}
