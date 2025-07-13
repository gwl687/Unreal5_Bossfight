// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Boss1Character.generated.h"

class UBoxComponent;

/**
 *
 */
UCLASS()
class MYCOMBATGAME1_API ABoss1Character : public ABaseCharacter
{
	GENERATED_BODY()
public:
	ABoss1Character();
protected:
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* skill1;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* attackRight;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* attackLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss1Property")
	float attackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss1Property")
	float TornadoAttackPower;
	UPROPERTY(EditAnywhere, Category = "Boss1Skill")
	TSubclassOf<AActor> TornadoPrefab;
	UPROPERTY(EditAnywhere, Category = "Boss1Skill")
	TSubclassOf<AActor> FireballPrefab;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* leftWeaponComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* rightWeaponComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool normalAttack1 = false;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttack(float dot);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackLeft();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackLeftEnd();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackRight();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackRightEnd();
	void PlayMontage(int Num);
	void NormalAttackEnd();
	void NormalAttack2();
	void NormalAttack2End();
	void TornadoAttack();
	void TornadoAttackEnd();
	void FireballAttack();
};
