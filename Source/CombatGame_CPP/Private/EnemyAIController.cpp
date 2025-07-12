// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "DebugHelper.h"
#include "EnemyBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	/*Super::BeginPlay();
	AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(GetPawn());
	if (enemy) {
		RunBehaviorTree(enemy->BehaviorTree);
	}*/
	////ÄÃµ½Íæ¼ÒµÄpawn
	//APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	//if (playerPawn) {
	//	/*SetFocus(playerPawn);
	//	MoveToActor(playerPawn, 150.0f);*/
	//	AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(GetPawn());
	//	RunBehaviorTree(enemy->BehaviorTree);
	//	UBlackboardComponent* blackboard = GetBlackboardComponent();
	//	blackboard->SetValueAsObject(FName("PlayerActor"), playerPawn);
	//}
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AEnemyBaseCharacter* enemy = Cast<AEnemyBaseCharacter>(InPawn);
	if (enemy) {
		RunBehaviorTree(enemy->BehaviorTree);
	}
}

void AEnemyAIController::SetAIDamage()
{
	UBlackboardComponent* blackboard = GetBlackboardComponent();
	if (blackboard) {
		blackboard->SetValueAsBool(FName("IsDamage"), true);
		APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (playerPawn) {
			SetFocus(playerPawn);
			blackboard->SetValueAsObject(FName("PlayerActor"), playerPawn);
		}
	}
}
