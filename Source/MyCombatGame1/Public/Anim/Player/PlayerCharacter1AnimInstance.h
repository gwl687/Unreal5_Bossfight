// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Anim/BaseAnimInstance.h"
#include "PlayerCharacter1AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYCOMBATGAME1_API UPlayerCharacter1AnimInstance : public UBaseAnimInstance
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
	/*UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool ;*/
};
