// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerBaseCharacter.generated.h"

class USpringArmComponent;//标识在这个类中要使用USpringArmComponent
class UCameraComponent;
class UInputMappingContext;
class  UInputAction;
struct FInputActionValue;
class ABaseWeapon;

UCLASS()
class COMBATGAME_CPP_API APlayerBaseCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	APlayerBaseCharacter();
	virtual void Tick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;//定义弹簧臂类型的变量
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

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "WeaponClass")
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> UnequipAnim;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	TObjectPtr<UAnimMontage> EquipAnim;

	UPROPERTY(EditAnyWhere, BluePrintReadOnly, Category = "AnimMontage")
	TArray<UAnimMontage*> AttackAnimList;
	UPROPERTY(BlueprintReadOnly, Category = "WeaponClass")
	ABaseWeapon* weapon;
	float attackRadius = 50.f;
	UPROPERTY(BlueprintReadOnly, Category = "GameMode")
	class ACombatGameMode* GameMode;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputMove(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void LookRotation(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void InputJump(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void ChangeAnim(const bool isChange);

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PlayAttackInPlayer();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	TArray<ABaseCharacter*> GetAttackRangeEnemy(const TArray<FHitResult> hitList);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PauseGameInput();
	void RegisterInput();
	void SpawnWeapon();
public:
	UPROPERTY(BlueprintReadWrite, Category = "MyVariable")
	bool isAttackAnim;

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void SwitchWeaponPoint(FName pointName);

	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void SetCharacterMovement(const EMovementMode movementMode);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void AddHealth(const float addValue);
	virtual void AttackDamage() override;
	virtual void HitResponse() override;
	virtual void DeathResponse() override;
};
