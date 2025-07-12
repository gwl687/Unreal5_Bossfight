// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMenuWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class COMBATGAME_CPP_API UStartMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UButton> StartGameBtn;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> QuitBtn;
	UFUNCTION()
	void OnStartGameBtnClick();
	UFUNCTION()
	void OnQuitClick();
};
