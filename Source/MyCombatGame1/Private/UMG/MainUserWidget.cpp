// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/MainUserWidget.h"
#include "Character/Enemy/Boss1Character.h"
#include "Character/PlayerCharacter1.h"
#include "Components/VerticalBox.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

bool UMainUserWidget::Initialize()
{
	if (!Super::Initialize()) {
		return false;
	}
	PlayerCharacter = Cast<APlayerCharacter1>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	BossCharacter = Cast<ABoss1Character>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoss1Character::StaticClass()));
	PlayerHealthBar->PercentDelegate.BindUFunction(this, FName("GetPlayerHealthProgress"));
	PlayerEnergyBar->PercentDelegate.BindUFunction(this, FName("GetPlayerEnergyProgress"));
	BossHealthBar->PercentDelegate.BindUFunction(this, FName("GetBossHealthProgress"));
	return true;
}

float UMainUserWidget::GetPlayerHealthProgress()
{
	if (PlayerCharacter) {
		return PlayerCharacter->getHealthProgress();
	}
	return 0.0f;
}

float UMainUserWidget::GetPlayerEnergyProgress()
{
	if (PlayerCharacter) {
		return PlayerCharacter->getEnergyProgress();
	}
	return 0.0f;
}

void UMainUserWidget::PlayBloodAnimation()
{
	PlayAnimation(BloodScreenAnim);
}

void UMainUserWidget::SetBoss(ABoss1Character* Boss)
{
	BossCharacter = Boss;
	if (Boss) {
		//显示Boss血条
		BossHealthBarPanel->SetVisibility(ESlateVisibility::Visible);
		//绑定Boss血条
		BossHealthBar->PercentDelegate.BindUFunction(this, FName("GetBossHealthProgress"));
	}
}


void UMainUserWidget::HideBossHealthBar()
{
	BossHealthBarPanel->SetVisibility(ESlateVisibility::Hidden);
}


float UMainUserWidget::GetBossHealthProgress()
{
	if (BossCharacter) {
		return BossCharacter->getHealthProgress();
	}
	return 0.0f;
}
