// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameMode1.h"
#include "Components/WidgetComponent.h"

void AGameMode1::BeginPlay()
{
	UUserWidget* widget = CreateWidget<UUserWidget>(GetWorld(), MainUIClass);
	if (widget) {
		widget->AddToViewport();
		MainUI = Cast<UMainUserWidget>(widget);
	}
	//ÓÎÏ·ÒôÀÖ
	/*if (AudioActorClass) {
		AudioActor = GetWorld()->SpawnActor<AAudioActor>(AudioActorClass);
	}*/
}
