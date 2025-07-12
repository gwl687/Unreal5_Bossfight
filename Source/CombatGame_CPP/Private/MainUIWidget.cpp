// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUIWidget.h"
#include "Components/ProgressBar.h"
#include "PlayerBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelper.h"
#include "Animation/WidgetAnimation.h"
#include "BossBaseCharacter.h"
#include "Components/VerticalBox.h"

bool UMainUIWidget::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	PlayerCharacter = Cast<APlayerBaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerHealthBar->PercentDelegate.BindUFunction(this, FName("GetPlayerHealthProgress"));
	BossHealthBar->PercentDelegate.BindUFunction(this, FName("GetBossHealthProgress"));
	return true;
}

float UMainUIWidget::GetPlayerHealthProgress()
{
	if (PlayerCharacter) {
		return PlayerCharacter->getHealthProgress();
	}
	return 0.0f;
}

void UMainUIWidget::PlayBloodAnimation()
{
	PlayAnimation(BloodScreenAnim);
}

void UMainUIWidget::SetBoss(ABossBaseCharacter* Boss)
{
	BossCharacter = Boss;
	if (Boss) {
		//显示Boss血条
		BossHealthBarPanel->SetVisibility(ESlateVisibility::Visible);
		//绑定Boss血条
		//BossHealthBar->PercentDelegate.BindUFunction(this, FName("GetBossHealthProgress"));
	}
}

void UMainUIWidget::HideBossHealthBar()
{
	BossHealthBarPanel->SetVisibility(ESlateVisibility::Hidden);
}


float UMainUIWidget::GetBossHealthProgress()
{
	if (BossCharacter) {
		return BossCharacter->getHealthProgress();
	}
	return 0.0f;
}

