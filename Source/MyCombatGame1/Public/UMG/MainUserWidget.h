// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Character/Enemy/Boss1Character.h"
#include "../Character/PlayerCharacter1.h"
#include "MainUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class MYCOMBATGAME1_API UMainUserWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PlayerHealthBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PlayerEnergyBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BossHealthBar;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* BossHealthBarPanel;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRef")
	class APlayerCharacter1 * PlayerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRef")
	ABoss1Character * BossCharacter;
	UPROPERTY(BlueprintReadWrite, Category = "WidgetAnim")
	class UWidgetAnimation* BloodScreenAnim;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	float GetPlayerHealthProgress();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	float GetPlayerEnergyProgress();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	float GetBossHealthProgress();
public:
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PlayBloodAnimation();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void SetBoss(ABoss1Character* Boss);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void HideBossHealthBar();
	virtual bool Initialize() override;
};
