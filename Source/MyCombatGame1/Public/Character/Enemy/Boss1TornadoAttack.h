// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OtherBaseActors/AttackActor.h"
#include "Boss1TornadoAttack.generated.h"

class UCapsuleComponent;
class USpringArmComponent;

/**
 * 
 */
UCLASS()
class MYCOMBATGAME1_API ABoss1TornadoAttack : public AAttackActor
{
	GENERATED_BODY()
public:
	ABoss1TornadoAttack();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	virtual void BeginPlay() override;
	void ActivateCapsule();
	void DeactivateCapsule();
public:

};
