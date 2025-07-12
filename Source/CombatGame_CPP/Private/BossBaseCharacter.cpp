// Fill out your copyright notice in the Description page of Project Settings.


#include "BossBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Animation/AnimMontage.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerBaseCharacter.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "CombatGameMode.h"
#include "Kismet/GameplayStatics.h"


void ABossBaseCharacter::PlayAttack()
{
	attackNum++;
	int32 rIndex = FMath::RandRange(0, AttackAnimList.Num() - 1);
	if (attackNum < 4) {
		GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimList[rIndex]);
	}
	else {
		GetMesh()->GetAnimInstance()->Montage_Play(BigAttackAnim);
		attackNum = 0;
	}
}

void ABossBaseCharacter::AttackDamage()
{
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * 500;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	TArray<AActor*> ignoreList;
	TArray<FHitResult> hitList;
	bool isResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 120.0f, ObjectTypes, true, ignoreList, EDrawDebugTrace::ForOneFrame, hitList, true);
	if (isResult) {
		APlayerBaseCharacter* player = GetAttackRangePlayer(hitList);
		if (player) {
			player->TakeHitDamage(20.0f);
		}
	}
}
APlayerBaseCharacter* ABossBaseCharacter::GetAttackRangePlayer(const TArray<FHitResult> hitList)
{
	APlayerBaseCharacter* player = nullptr;
	for (FHitResult hitRes : hitList) {
		player = Cast<APlayerBaseCharacter>(hitRes.GetActor());
		if (player) {
			break;
		}
	}
	return player;
}

void ABossBaseCharacter::DeathResponse()
{
	AAIController* controller = Cast<AAIController>(GetController());
	if (controller) {
		controller->BrainComponent->StopLogic("");
		controller->ClearFocus(EAIFocusPriority::LastFocusPriority);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ACombatGameMode* gameMode =  Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (gameMode) {
			gameMode->HideBossHealthBar();
		}
	}
}
