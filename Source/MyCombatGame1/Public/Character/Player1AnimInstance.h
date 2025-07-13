// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Player1AnimInstance.generated.h"

class ABaseCharacter;
/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API UPlayer1AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	ABaseCharacter* ownerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	float speed;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	float direction;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isFalling;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isJumpingAttack = false;

	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isDeath;
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_CanCombo(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackCollision(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_NormalAttackCollisionCancel(UAnimNotify* Notify);
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimValue")
	bool isAttackAnim;
};
