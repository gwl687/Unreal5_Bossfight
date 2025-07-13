// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/TaskSetAISpeed.h"
#include "Character/BaseCharacter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Anim\BaseAnimInstance.h"
#include "BehaviorTree\BlackboardComponent.h"

UTaskSetAISpeed::UTaskSetAISpeed()
{
	NodeName = FString("SetAISpeed");
	bNotifyTick = true;
}

void UTaskSetAISpeed::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	ABaseCharacter* enemy = Cast<ABaseCharacter>(controller->GetPawn());
	if (enemy->canMove) {
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}

EBTNodeResult::Type UTaskSetAISpeed::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return EBTNodeResult::Failed;
	ABaseCharacter* enemy = Cast<ABaseCharacter>(controller->GetPawn());
	if (!enemy) return EBTNodeResult::Failed;
	//Զ�̹����ͽ��̹�����ѡһ
	//UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	int moveMode = FMath::RandRange(0, 1);
	//�����ƶ�
	if (moveMode == 0) {
		enemy->speed = 600;
	}
	//�����ƶ�
	else {
		enemy->speed = 1200;
	}
	//enemy->GetCharacterMovement()->MaxWalkSpeed = enemy->speed;
	return EBTNodeResult::InProgress;
}
