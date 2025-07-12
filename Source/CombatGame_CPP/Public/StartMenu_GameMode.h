// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartMenu_GameMode.generated.h"

/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API AStartMenu_GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="StartGameClass")
	TSubclassOf<UStartMenuWidget> StartMenuClass;
};
