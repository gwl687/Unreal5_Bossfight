// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Player/PlayerCharacter1AnimInstance.h"
#include "Character\PlayerCharacter1.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


void UPlayerCharacter1AnimInstance::NativeInitializeAnimation()
{
	//ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, AnimCharacter!"));
}

void UPlayerCharacter1AnimInstance::NativeUpdateAnimation(float deltaTime)
{
	if (ownerCharacter) {
		//获取动画蓝图对应角色速度
		FVector velocity = ownerCharacter->GetVelocity();
		speed = velocity.Length();
		//获取动画蓝图对应方向
		FRotator rotation = ownerCharacter->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
		//判断是否正在掉落
		UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
		isFalling = movement->IsFalling();
	}
}

//播放普通攻击动画
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackCollision(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollision();
}
//判断是否可以连击
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollisionCancel();
}
void UPlayerCharacter1AnimInstance::AnimNotify_CanCombo(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}
//当前攻击结束
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackEnd();
}

