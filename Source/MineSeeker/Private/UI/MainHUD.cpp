// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "GM_MineSeeker.h"


void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(EMatchState::WaitingToStart, CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass));
	GameWidgets.Add(EMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(EMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));
	GameWidgets.Add(EMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), GameProgressWidgetClass));
	for (auto GameWidgetPair : GameWidgets)
	{
		const auto GameWidget = GameWidgetPair.Value;
		if (!GameWidget) continue;

		GameWidget->AddToViewport();
		GameWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	
	if (GetWorld())
	{
		const auto GameMode = Cast<AGM_MineSeeker>(GetWorld()->GetAuthGameMode());
		if (GameMode)
		{
			GameMode->OnMatchStateChanged.AddUObject(this, &AMainHUD::OnMatchStateChanged);
		}
	}
}

void AMainHUD::OnMatchStateChanged(EMatchState State) // Функция должна повторять сигнатуру делегата
{
	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (GameWidgets.Contains(State))
	{
		CurrentWidget = GameWidgets[State];
	}

	if (CurrentWidget)
	{
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}