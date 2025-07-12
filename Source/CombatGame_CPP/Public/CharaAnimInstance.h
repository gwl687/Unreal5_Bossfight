// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharaAnimInstance.generated.h"


/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API UCharaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	class ABaseCharacter* ownerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	float speed;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	float direction;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isFalling;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isAttackAnim;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isDeath;
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_WeaponToHand(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_SwitchWeaponPose(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_UnequipWeapon(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_EquipEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_AttackEnd(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "AnimNotify")
	void AnimNotify_AttackDamage(UAnimNotify* Notify);
	UFUNCTION()
	void SwitchWeaponPoint(FName pointName);

};
