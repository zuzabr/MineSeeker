// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
#include "MainMenuWidget.generated.h"


class UButton;


UCLASS()
class MINESEEKER_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
		UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGameButton;

private:

	UFUNCTION()
		void OnStartGame();

	UFUNCTION()
		void OnQuitGame();
	
};
