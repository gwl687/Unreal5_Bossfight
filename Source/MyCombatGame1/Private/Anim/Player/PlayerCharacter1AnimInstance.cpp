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

//������ͨ��������
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackCollision(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollision();
}
//�ж��Ƿ��������
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollisionCancel();
}
void UPlayerCharacter1AnimInstance::AnimNotify_CanCombo(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}
//��ǰ��������
void UPlayerCharacter1AnimInstance::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackEnd();
}

