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
	//	//��ȡ������ͼ��Ӧ��ɫ�ٶ�
	//	FVector velocity = ownerCharacter->GetVelocity();
	//	speed = velocity.Length();
	//	//��ȡ������ͼ��Ӧ����
	//	FRotator rotation = ownerCharacter->GetActorRotation();
	//	direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
	//	//�ж��Ƿ����ڵ���
	//	UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
	//	isFalling = movement->IsFalling();
	//}
}
//������ײ�����
void UPlayer1AnimInstance::AnimNotify_NormalAttackCollision(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollision();
}


//������ײ����ʧ
void UPlayer1AnimInstance::AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollisionCancel();
}


void UPlayer1AnimInstance::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackEnd();
}
//�ж��Ƿ�������
void UPlayer1AnimInstance::AnimNotify_CanCombo(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}



//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, UE5!"));
