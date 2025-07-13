// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Boss1AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter1.h"
#include "BehaviorTree\BlackboardComponent.h"
#include "Character/Enemy/Boss1Character.h"
#include "Character\PlayerCharacter1.h"

ABoss1AIController::ABoss1AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void ABoss1AIController::BeginPlay()
{
	Super::BeginPlay();
}

void ABoss1AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ABoss1Character* boss1 = Cast<ABoss1Character>(InPawn);
	if (boss1) {
		RunBehaviorTree(boss1->BehaviorTree);
	}
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ABoss1AIController::OnperceptionUpdate);
	/*ABoss1Character* boss1 = Cast<ABoss1Character>(InPawn);
	RunBehaviorTree(boss1->BehaviorTree);*/
	/*if (boss1) {
		ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		UBlackboardComponent* blackboard = GetBlackboardComponent();
		if (player && blackboard) {
			SetFocus(player);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("blackboard"));
			blackboard->SetValueAsObject(FName("PlayerActor"), player);
		}
	}*/
}

void ABoss1AIController::OnperceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	APlayerCharacter1* player = Cast<APlayerCharacter1>(Actor);
	if (player) {
		UBlackboardComponent* blackboard = GetBlackboardComponent();
		if (blackboard) {
			blackboard->SetValueAsObject(FName("PlayerActor"), player);
			//设置第一波攻击为近距离还是远距离
			int AttackDistance = FMath::RandRange(0, 1);
			AttackDistance = 1;
			if (AttackDistance) {
				blackboard->SetValueAsBool(FName("IsCloseAttack"), true);
			}
			else {
				blackboard->SetValueAsBool(FName("IsCloseAttack"), false);
			}
		}
	}
}
