// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

class UButton;

UCLASS()
class MINESEEKER_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
		UButton* ClearPauseButton;

private:
	UFUNCTION()
		void OnClearPause();
	
};
