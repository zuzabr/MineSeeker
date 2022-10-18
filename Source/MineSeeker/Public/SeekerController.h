// Zuzabr Games 2022 All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MineSeekerCoreTypes.h"
#include "SeekerController.generated.h"



UCLASS()
class MINESEEKER_API ASeekerController : public APlayerController
{
	GENERATED_BODY()

public:

	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void OnRMBClicked();

private:
	void OnPauseGame();
};
