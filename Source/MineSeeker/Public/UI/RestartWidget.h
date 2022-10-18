// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
#include "RestartWidget.generated.h"

class UButton;

UCLASS()
class MINESEEKER_API URestartWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* RestartButton;

private:
	UFUNCTION()
		void RestartGame();
};
