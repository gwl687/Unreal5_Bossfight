// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "BossBaseCharacter.generated.h"

class UBehaviorTree;
class UAnimMontage;
/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API ABossBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
	TArray<TObjectPtr<UAnimMontage>> AttackAnimList;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> BigAttackAnim;
	UFUNCTION()
	APlayerBaseCharacter* GetAttackRangePlayer(const TArray<FHitResult> hitList);
	int32 attackNum = 0;
	virtual void DeathResponse() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	virtual void PlayAttack() override;
	virtual void AttackDamage() override;
};
