// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "StartMenuWidget.h"
#include "Kismet/GamePlayStatics.h"

void AStartMenu_GameMode::BeginPlay()
{
	if (StartMenuClass) {
		UStartMenuWidget* widget = CreateWidget<UStartMenuWidget>(GetWorld(), StartMenuClass);
		widget->AddToViewport();
		APlayerController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		FInputModeUIOnly uiOnly;
		pController->bShowMouseCursor = true;
	}
}
