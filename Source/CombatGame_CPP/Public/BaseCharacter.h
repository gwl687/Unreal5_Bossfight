// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class COMBATGAME_CPP_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthValue");
	float maxHealth = 100;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> HitMontage;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void MyDelay(float delayTime, FName FunctionName);
public:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = "AI")
	bool isAttacking = false;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void AttackDamage();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void TakeHitDamage(const float damageValue);
	//角色的伤害响应
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void HitResponse();
	//角色的死亡响应
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	virtual void DeathResponse();
	UFUNCTION()
	virtual void PlayAttack();
	FORCEINLINE float getHealthProgress() { return health / maxHealth; }
};
