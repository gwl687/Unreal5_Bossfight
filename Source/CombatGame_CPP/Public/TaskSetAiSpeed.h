// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskSetAiSpeed.generated.h"

/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API UTaskSetAiSpeed : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskSetAiSpeed();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI");
	float speed = 175;
};
