// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "EnemyBaseCharacter.generated.h"

class UHealthBarWidget;
class UWidgetComponent;
class APlayerBaseCharacter;
class UParticleSystem;
class AHealthPack;
/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API AEnemyBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	AEnemyBaseCharacter();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(BlueprintReadWrite, Category = "MyVariable")
	bool isDamage = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Anim")
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UIWidget")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ParticleVar")
	TObjectPtr<UParticleSystem> DeathParticle;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthPack")
	TSubclassOf<AHealthPack> HealthPackClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "WidgetComp")
	UWidgetComponent* HealthBar;
	UFUNCTION()
	void DestroyEnemy();
	virtual void DeathResponse() override;
	virtual void HitResponse() override;
public:
	UPROPERTY(Editanywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	APlayerBaseCharacter* GetAttackRangePlayer(const TArray<FHitResult> hitList);
	virtual void AttackDamage() override;
	virtual void PlayAttack() override;
};
