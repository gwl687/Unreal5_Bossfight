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
		//获取动画蓝图对应角色速度
		FVector velocity = ownerCharacter->GetVelocity();
		speed = velocity.Length();
		//获取移动方向
		FRotator rotation = ownerCharacter->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
		//判断是否正在掉落
		UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
		isFalling = movement->IsFalling();
		//将当前角色转换为player
		APlayerBaseCharacter* player = Cast<APlayerBaseCharacter>(ownerCharacter);
		if (player) {
			isAttackAnim = player->isAttackAnim;//赋值当前的动画状态
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

//敌人攻击结束
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
