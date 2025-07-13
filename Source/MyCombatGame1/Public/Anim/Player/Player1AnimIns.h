// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/BaseAnimInstance.h"
#include "Player1AnimIns.generated.h"

/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API UPlayer1AnimIns : public UBaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;
protected:
	
public:
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackCollision(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_CanCombo(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_EndRunning(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_Jumping(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_Landing(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_Print(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_StopUpperBlending(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_CanReleaseR(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_ReleaseR(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_EnterIdleAndMove(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_Death(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_SheathSwordEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_rollStart(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_rollEnd(UAnimNotify* Notify);
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isJumpingState = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isSheathSwordEndRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isRolling = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isTravelEndRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	bool isUpperBodyBlend = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool isAttacking = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool isJumpingAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	bool canMoveAndJump = true;
};
