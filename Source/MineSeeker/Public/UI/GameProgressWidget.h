// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameProgressWidget.generated.h"

class UButton;

UCLASS()
class MINESEEKER_API UGameProgressWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* PauseButton;

private:
    UFUNCTION()
    void OnPauseSet();	
	
};
