// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/BaseAnimInstance.h"
#include "Boss1AnimInstance.generated.h"

/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API UBoss1AnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()
protected:
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttack(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalDamageEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_TornadoAttack(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_BattleMode(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttack2(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttack2End(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_EnterCombat(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackLeftCollision(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackLeftCollisionEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackRightCollision(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackRightCollisionEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_CanMove(UAnimNotify* Notify);
public:
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool attackMode;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool normalAttack1;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool normalAttack2;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool skill1;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hurtBack;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hurtFront;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hurtLeft;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hurtRight;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	int hurtDirection;
};
