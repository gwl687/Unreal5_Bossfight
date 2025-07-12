// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUIWidget.generated.h"

class ABossBaseCharacter;
/**
 *
 */

UCLASS()
class COMBATGAME_CPP_API UMainUIWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PlayerHealthBar;
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* BossHealthBar;
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* BossHealthBarPanel;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRef")
	class APlayerBaseCharacter* PlayerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "PlayerRef")
	ABossBaseCharacter* BossCharacter;
	UPROPERTY(BlueprintReadWrite, Category = "WidgetAnim")
	class UWidgetAnimation* BloodScreenAnim;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	float GetPlayerHealthProgress();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	float GetBossHealthProgress();
public:
	UFUNCTION(BlueprintCallable,Category="MyFunction")
	void PlayBloodAnimation();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void SetBoss(ABossBaseCharacter* Boss);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void HideBossHealthBar();
};
