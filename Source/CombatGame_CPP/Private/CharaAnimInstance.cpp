// Fill out your copyright notice in the Description page of Project Settings.


#include "CharaAnimInstance.h"
#include "BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerBaseCharacter.h"
#include "DebugHelper.h"
#include "EnemyBaseCharacter.h"
#include "KismetAnimationLibrary.h"

void UCharaAnimInstance::NativeInitializeAnimation()
{
	ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UCharaAnimInstance::NativeUpdateAnimation(float deltaTime)
{
	if (ownerCharacter) {
		//��ȡ������ͼ��Ӧ��ɫ�ٶ�
		FVector velocity = ownerCharacter->GetVelocity();
		speed = velocity.Length();
		//��ȡ�ƶ�����
		FRotator rotation = ownerCharacter->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
		//�ж��Ƿ����ڵ���
		UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
		isFalling = movement->IsFalling();
		//����ǰ��ɫת��Ϊplayer
		APlayerBaseCharacter* player = Cast<APlayerBaseCharacter>(ownerCharacter);
		if (player) {
			isAttackAnim = player->isAttackAnim;//��ֵ��ǰ�Ķ���״̬
		}
		if (ownerCharacter->getHealthProgress() <= 0) {
			isDeath = true;
		}
	}
}

void UCharaAnimInstance::AnimNotify_WeaponToHand(UAnimNotify* Notify)
{
	Debug::Print("Run Weapon To Hand");
	SwitchWeaponPoint(FName("WeaponToHandPoint"));
}

void UCharaAnimInstance::AnimNotify_SwitchWeaponPose(UAnimNotify* Notify)
{
	//Debug::Print("Run Switch Weapon Pose");
	SwitchWeaponPoint(FName("WeaponAttackPoint"));
}

void UCharaAnimInstance::AnimNotify_UnequipWeapon(UAnimNotify* Notify)
{
	SwitchWeaponPoint(FName("NormalWeaponPoint"));
}

void UCharaAnimInstance::AnimNotify_EquipEnd(UAnimNotify* Notify)
{
	APlayerBaseCharacter* playerCharacter = Cast<APlayerBaseCharacter>(ownerCharacter);
	if (playerCharacter) {
		playerCharacter->SetCharacterMovement(EMovementMode::MOVE_Walking);
	}
}

//���˹�������
void UCharaAnimInstance::AnimNotify_AttackEnd(UAnimNotify* Notify)
{
	ABaseCharacter* enemyCharacter = Cast<ABaseCharacter>(ownerCharacter);
	if (enemyCharacter) {
		enemyCharacter->isAttacking = false;
	}
}

void UCharaAnimInstance::AnimNotify_AttackDamage(UAnimNotify* Notify)
{
	if (ownerCharacter) {
		ownerCharacter->AttackDamage();
	}
}

void UCharaAnimInstance::SwitchWeaponPoint(FName pointName)
{
	APlayerBaseCharacter* playerCharacter = Cast<APlayerBaseCharacter>(ownerCharacter);
	if (playerCharacter) {
		playerCharacter->SwitchWeaponPoint(pointName);
	}
}
