// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

class ABaseCharacter;
/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float deltaTime) override;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isDead;
	UPROPERTY(BlueprintReadWrite, Category = "AnimValue")
	bool getHit;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hitFront;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hitBack;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hitLeft;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool hitRight;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	int hitNum = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimValue")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimValue")
	bool isFalling;
	
protected:
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	ABaseCharacter* ownerCharacter;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	float direction;
	UPROPERTY(BlueprintReadOnly, Category = "AnimValue")
	bool isDeath;
};
