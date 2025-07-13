// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "../UMG/MainUserWidget.h"
#include "GameMode1.generated.h"

/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API AGameMode1 : public AGameModeBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainUIClass;
	UPROPERTY(BlueprintReadOnly, Category = "UIWidget")
	UMainUserWidget* MainUI;
public:
	virtual void BeginPlay() override;
};
