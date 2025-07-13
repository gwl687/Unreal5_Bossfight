// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/TaskAttackPlayer.h"
#include "Character\PlayerCharacter1.h"
#include "Character/BaseCharacter.h"
#include "AIController.h"
#include "Character\Enemy\Boss1Character.h"
#include "Anim\Enemy\Boss1AnimInstance.h"
#include "Kismet\GameplayStatics.h"

UTaskAttackPlayer::UTaskAttackPlayer()
{
	NodeName = FString("AttackPlayer");
	bNotifyTick = true;
}

EBTNodeResult::Type UTaskAttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* controller = OwnerComp.GetAIOwner();
	if (!controller) return EBTNodeResult::Failed;
	ABoss1Character* enemy = Cast<ABoss1Character>(controller->GetPawn());
	APlayerCharacter1* playerCharacter = Cast<APlayerCharacter1>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	FVector ToPlayer = (playerCharacter->GetActorLocation() - enemy->GetActorLocation()).GetSafeNormal();
	FVector EnemyRightVector = enemy->GetActorRightVector();
	float dot = FVector::DotProduct(EnemyRightVector, ToPlayer);
	if (!enemy)return EBTNodeResult::Failed;
	//���ѡ�񹥻�ģʽ
	int32 AttackMode = FMath::RandRange(0, 1);
	switch (AttackMode)
	{
	case 0: {
		//��ͨ����
		int32 AttackNum = FMath::RandRange(0, 1);
		Cast<UBoss1AnimInstance>(enemy->GetMesh()->GetAnimInstance())->attackMode = true;
		enemy->NormalAttack(dot);
		//if (dot >= 0) {
		//	enemy->NormalAttackRight();
		//	//enemy->GetMesh()->GetAnimInstance()->Montage_Play(s);
		//	//Cast<UBoss1AnimInstance>(enemy->GetMesh()->GetAnimInstance())->normalAttack1 = true;
		//}
		//else {
		//	enemy->NormalAttackLeft();
		//	//enemy->GetMesh()->GetAnimInstance()->Montage_Play();
		//	//Cast<UBoss1AnimInstance>(enemy->GetMesh()->GetAnimInstance())->normalAttack2 = true;
		//}
		break;
	}
	case 1:
		//����1
		enemy->TornadoAttack();
		break;
	default:
		break;
	}
	return EBTNodeResult::Succeeded;
}

void UTaskAttackPlayer::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

