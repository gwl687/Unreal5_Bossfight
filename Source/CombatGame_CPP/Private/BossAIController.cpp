// Fill out your copyright notice in the Description page of Project Settings.


#include "BossAIController.h"
#include "BossBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABossBaseCharacter* boss = Cast<ABossBaseCharacter>(InPawn);
	if (boss) {
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		RunBehaviorTree(boss->BehaviorTree);
		UBlackboardComponent* blackboard = GetBlackboardComponent();
		if (player&&blackboard) {
			SetFocus(player);
			blackboard->SetValueAsObject(FName("PlayerActor"), player);
		}
	}
}
