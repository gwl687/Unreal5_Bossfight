// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TaskAttackPlayer.generated.h"

/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API UTaskAttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UTaskAttackPlayer();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
