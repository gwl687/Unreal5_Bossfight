// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class MYCOMBATGAME1_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterProperty")
	float maxHealth;
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
	AActor* MyHitComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TObjectPtr<UAnimMontage> HitMontageFront;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TObjectPtr<UAnimMontage> HitMontageBack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TObjectPtr<UAnimMontage> HitMontageLeft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TObjectPtr<UAnimMontage> HitMontageRight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Anim")
	TObjectPtr<UAnimMontage> DeathMontage;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage*> AttackMontageList;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void HitResponse();

	void DestroySelf();
public:
	UPROPERTY(BlueprintReadOnly, Category = "Property")
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
	float canMove = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Property")
	float attackDamage;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void AttackDamage();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void PlayAttack();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void TakeHit(float damage, FVector AttackerLocation);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	AActor* GetAttackRangeActor(const TArray<FHitResult> hitList, FName MyTag);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void DeathResponse();
	//血条百分比
	FORCEINLINE float getHealthProgress();
};
