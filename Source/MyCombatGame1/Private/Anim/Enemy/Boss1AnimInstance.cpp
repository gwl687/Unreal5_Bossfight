// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/Enemy/Boss1AnimInstance.h"
#include "Character/Enemy/Boss1Character.h"
#include "Components\BoxComponent.h"

void UBoss1AnimInstance::AnimNotify_NormalAttack(UAnimNotify* Notify)
{
	//Cast<ABoss1Character>(ownerCharacter)->NormalAttack();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, Anim!"));
}

void UBoss1AnimInstance::AnimNotify_NormalDamageEnd(UAnimNotify* Notify)
{

}

void UBoss1AnimInstance::AnimNotify_NormalAttackEnd(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->NormalAttackEnd();
}

void UBoss1AnimInstance::AnimNotify_TornadoAttack(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->TornadoAttack();
}

void UBoss1AnimInstance::AnimNotify_BattleMode(UAnimNotify* Notify)
{
	/*normalAttack1 = false;
	normalAttack2 = false;*/
}

void UBoss1AnimInstance::AnimNotify_NormalAttack2(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->NormalAttack2();

}

void UBoss1AnimInstance::AnimNotify_NormalAttack2End(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->NormalAttack2End();
}
//进入攻击动作
void UBoss1AnimInstance::AnimNotify_EnterCombat(UAnimNotify* Notify)
{
	getHit = false;
}

void UBoss1AnimInstance::AnimNotify_NormalAttackLeftCollision(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UBoss1AnimInstance::AnimNotify_NormalAttackLeftCollisionEnd(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UBoss1AnimInstance::AnimNotify_NormalAttackRightCollision(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void UBoss1AnimInstance::AnimNotify_NormalAttackRightCollisionEnd(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UBoss1AnimInstance::AnimNotify_CanMove(UAnimNotify* Notify)
{
	Cast<ABoss1Character>(ownerCharacter)->canMove = true;
}




