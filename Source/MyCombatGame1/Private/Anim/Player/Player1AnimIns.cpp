// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Player/Player1AnimIns.h"
#include "KismetAnimationLibrary.h"
#include "Character\BaseCharacter.h"
#include "Character\PlayerCharacter1.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayer1AnimIns::NativeInitializeAnimation()
{
	ownerCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());
}

void UPlayer1AnimIns::NativeUpdateAnimation(float deltaTime)
{
	if (ownerCharacter) {
		//获取动画蓝图对应角色速度
		FVector velocity = ownerCharacter->GetVelocity();
		speed = velocity.Size();
		//获取动画蓝图对应方向
		FRotator rotation = ownerCharacter->GetActorRotation();
		direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
		//判断是否正在掉落
		UCharacterMovementComponent* movement = ownerCharacter->GetCharacterMovement();
		isFalling = movement->IsFalling();
		if (isSheathSwordEndRunning) {
			movement->MaxAcceleration = 99999;
		}
		else {
			movement->MaxAcceleration = 2048;
		}
	}
	
}

void UPlayer1AnimIns::AnimNotify_NormalAttackCollision(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollision();
}

void UPlayer1AnimIns::AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackCollisionCancel();
}

void UPlayer1AnimIns::AnimNotify_CanCombo(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
	Cast<APlayerCharacter1>(ownerCharacter)->canMoveAndJump = true;
}

void UPlayer1AnimIns::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->NormalAttackEnd();
}

void UPlayer1AnimIns::AnimNotify_EndRunning(UAnimNotify* Notify)
{
	isUpperBodyBlend = false;
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}

void UPlayer1AnimIns::AnimNotify_Jumping(UAnimNotify* Notify)
{
	isJumpingState = true;
}

void UPlayer1AnimIns::AnimNotify_Landing(UAnimNotify* Notify)
{
	isJumpingState = false;
	isAttacking = false;
	isRunning = false;
	Cast<APlayerCharacter1>(ownerCharacter)->canCombo = true;
}

void UPlayer1AnimIns::AnimNotify_Print(UAnimNotify* Notify)
{

}

void UPlayer1AnimIns::AnimNotify_StopUpperBlending(UAnimNotify* Notify)
{
	isUpperBodyBlend = false;
	ownerCharacter->GetCharacterMovement()->MaxWalkSpeed = 600;
}

void UPlayer1AnimIns::AnimNotify_CanReleaseR(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->canReleaseR = true;
}

void UPlayer1AnimIns::AnimNotify_ReleaseR(UAnimNotify* Notify)
{
	Cast<APlayerCharacter1>(ownerCharacter)->ReleaseR();
}

void UPlayer1AnimIns::AnimNotify_EnterIdleAndMove(UAnimNotify* Notify)
{
	if (Cast<APlayerCharacter1>(ownerCharacter)) {
		Cast<APlayerCharacter1>(ownerCharacter)->EnterIdleAndMove();
	}
	//Cast<APlayerCharacter1>(ownerCharacter)->EnterIdleAndMove();
	//ownerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void UPlayer1AnimIns::AnimNotify_Death(UAnimNotify* Notify)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, death!"));
	/*GetSkelMeshComponent()->bPauseAnims = true;
	GetSkelMeshComponent()->bNoSkeletonUpdate = true;*/
	//GetSkelMeshComponent()->bNoSkeletonUpdate = false;
}

void UPlayer1AnimIns::AnimNotify_SheathSwordEnd(UAnimNotify* Notify)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, SheathSwordEnd!"));
	isUpperBodyBlend = false;
	isSheathSwordEndRunning = true;
}

void UPlayer1AnimIns::AnimNotify_rollStart(UAnimNotify* Notify)
{
	isRolling = true;
	//isRunning = false;
}

void UPlayer1AnimIns::AnimNotify_rollEnd(UAnimNotify* Notify)
{
	isRolling = false;
	if (isRunning) {
		Cast<APlayerCharacter1>(ownerCharacter)->rollToRun();
	}
}

