// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MineSeekerCoreTypes.h"
#include "MainHUD.generated.h"

UCLASS()
class MINESEEKER_API AMainHUD : public AHUD
{
	GENERATED_BODY()



protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameProgressWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
		TMap<EMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;


	void OnMatchStateChanged(EMatchState State);
	
};
