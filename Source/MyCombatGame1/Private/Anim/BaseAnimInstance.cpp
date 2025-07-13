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
		//��ȡ������ͼ��Ӧ��ɫ�ٶ�
		FVector velocity = ownerCharacter->GetVelocity();
		speed = velocity.Length();
		//��ȡ������ͼ��Ӧ����
		FRotator rotation = ownerCharacter->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
		//�ж��Ƿ����ڵ���
		UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
		isFalling = movement->IsFalling();
	}
}



