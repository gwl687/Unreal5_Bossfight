// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

bool UStartMenuWidget::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	StartGameBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnStartGameBtnClick);
	QuitBtn->OnClicked.AddDynamic(this, &UStartMenuWidget::OnQuitClick);
	return true;
}

void UStartMenuWidget::OnStartGameBtnClick()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName("SunTemple"));
}

void UStartMenuWidget::OnQuitClick()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr,EQuitPreference::Quit,true);
}
