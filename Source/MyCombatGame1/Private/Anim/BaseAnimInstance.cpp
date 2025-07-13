// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/BaseAnimInstance.h"
#include "Character/BaseCharacter.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBaseAnimInstance::NativeInitializeAnimation()
{
	ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UBaseAnimInstance::NativeUpdateAnimation(float deltaTime)
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



