// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "PlayerCharacter1.generated.h"


class USpringArmComponent;//标识在这个类中要使用USpringArmComponent
class UCameraComponent;
class UInputMappingContext;
class UNiagaraComponent;
class  UInputAction;
struct FInputActionValue;
class ABaseWeapon;
class UCapsuleComponent;
class UBoxComponent;

UCLASS()
class MYCOMBATGAME1_API APlayerCharacter1 : public ABaseCharacter
{
	GENERATED_BODY()

protected:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* FollowCamera;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage*> AttackAnimList;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* TravelStart;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* TravelStop;
	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	UAnimMontage* StartRolling;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player1Property")
	UNiagaraComponent* PlayerGhostEffect;
	//基础攻击力
	UPROPERTY(BlueprintReadOnly, Category = "Player1Property")
	float NormalAttackPower = 15;
	//技能1攻击力
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player1Property")
	float skill1AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player1Property")
	float isPlayerRunning = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player1Property")
	float isJumpingAttack = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player1Property")
	float isAbilityRCharging = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player1Property")
	FVector moveDir;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputMove(const FVector2D axis2D);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputLookRotation(const FVector2D axis2D);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputJump(const bool isJump);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputDodge(const bool isDodge);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputPlayerAttack();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputAbilityR();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputAbilityRightButton();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputAbilityReleaseR();

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputRun();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputRunToWalk(bool isInput);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void RunToWalk();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void DeactivatePlayerGhostEffect();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	FVector2D LastStoredMoveInput;
	virtual void BeginPlay() override;
	virtual void HitResponse() override;
	virtual void DeathResponse() override;
public:
	APlayerCharacter1();
	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	int attackIndex = 0;
	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	bool canCombo = true;
	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	bool canReleaseR = false;
	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	bool canMoveAndJump = true;
	UPROPERTY(EditAnywhere, Category = "AnimMontage")
	bool canRechargeR = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* weaponComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MyProperty")
	float  maxEnergy = 100;
	float  energy;
	float  RunningCdCnt = 0;
	float  RAbilityCdCnt = 0;
	bool enterRunningCd = false;
	bool runningCdState = false;
	bool enterRAbilityCd = false;
	bool RAbilityCdState = false;
	bool isRunning = false;
	bool isSwordOnBack = false;
	void PlayNormalAttack();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackCollision();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackCollisionCancel();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void NormalAttackEnd();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void EnterIdleAndMove();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void ReleaseR();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void rollToRun();
	//获取能量条百分比
	FORCEINLINE float getEnergyProgress();
};
