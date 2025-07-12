// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy2AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "PlayerBaseCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DebugHelper.h"
#include "Kismet/GameplayStatics.h"

AEnemy2AIController::AEnemy2AIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerception");
}

void AEnemy2AIController::BeginPlay()
{
	Super::BeginPlay();
	//AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy2AIController::OnperceptionUpdate);
}

void AEnemy2AIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemy2AIController::OnperceptionUpdate);
}

void AEnemy2AIController::OnperceptionUpdate(AActor* Actor, FAIStimulus Stimulus)
{
	APlayerBaseCharacter* player = Cast<APlayerBaseCharacter>(Actor);
	if (player) {
		UBlackboardComponent* blackboard = GetBlackboardComponent();
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("jiancedaoplayer"));
		if (blackboard) {
			blackboard->SetValueAsObject(FName("PlayerActor"), player);
		}
	}
}
