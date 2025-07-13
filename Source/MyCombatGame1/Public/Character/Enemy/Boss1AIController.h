// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Boss1AIController.generated.h"

/**
 * 
 */
UCLASS()
class MYCOMBATGAME1_API ABoss1AIController : public AAIController
{
	GENERATED_BODY()
public:
	ABoss1AIController();
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyComponents")
	class UAIPerceptionComponent* AIPerceptionComponent;
	UFUNCTION()
	void OnperceptionUpdate(AActor* Actor, FAIStimulus Stimulus);
};
