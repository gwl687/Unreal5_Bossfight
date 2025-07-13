// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Player1AnimInstance.h"
#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/PlayerCharacter1.h"
#include "Components/BoxComponent.h"
#include "KismetAnimationLibrary.h"

void UPlayer1AnimInstance::NativeInitializeAnimation()
{
	//ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, Anim!"));
}

void UPlayer1AnimInstance::NativeUpdateAnimation(float deltaTime)
{
	//if (ownerCharacter) {
	//	//获取动画蓝图对应角色速度
	//	FVector velocity = ownerCharacter->GetVelocity();
	//	speed = velocity.Length();
	//	//获取动画蓝图对应方向
	//	FRotator rotation = ownerCharacter->GetActorRotation();
	//	direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
	//	//判断是否正在掉落
	//	UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
	//	isFalling = movement->IsFalling();
	//}
}
//攻击碰撞体出现
void UPlayer1AnimInstance::AnimNotify_NormalAttackCollision(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollision();
}


//攻击碰撞体消失
void UPlayer1AnimInstance::AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollisionCancel();
}


void UPlayer1AnimInstance::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackEnd();
}
//判断是否能连击
void UPlayer1AnimInstance::AnimNotify_CanCombo(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}



//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, UE5!"));
