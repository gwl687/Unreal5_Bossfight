// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBaseCharacter.h"
#include "BaseWeapon.h"
#include "BossBaseCharacter.h"
#include "Camera/CameraComponent.h"//导入摄像机头文件
#include "CombatGameMode.h"
#include "DebugHelper.h"
#include "EnemyBaseCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"//导入弹簧臂组件头文件
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

APlayerBaseCharacter::APlayerBaseCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
}

void APlayerBaseCharacter::Tick(float deltaTime)
{
	//	Super::Tick(deltaTime);
}

void APlayerBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	RegisterInput();
	SpawnWeapon();
	GameMode = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void APlayerBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EhancedInputComponent) {
		EhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerBaseCharacter::InputMove);
		EhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerBaseCharacter::LookRotation);
		EhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APlayerBaseCharacter::InputJump);
		EhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APlayerBaseCharacter::InputJump);
	}
}

void APlayerBaseCharacter::InputMove(const FInputActionValue& Value)
{
	FVector2D axis2D = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		FRotator rotation = Controller->GetControlRotation();
		FRotator yawRotation(0, rotation.Yaw, 0.0f);
		FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(forwardDir, axis2D.X);
		AddMovementInput(rightDir, axis2D.Y);
	}
}

void APlayerBaseCharacter::LookRotation(const FInputActionValue& Value)
{
	FVector2D axis2D = Value.Get<FVector2D>();
	if (Controller != nullptr) {
		AddControllerYawInput(axis2D.X);
		AddControllerPitchInput(axis2D.Y);
	}
}

void APlayerBaseCharacter::InputJump(const FInputActionValue& Value)
{
	bool isJump = Value.Get<bool>();
	isJump ? Jump() : StopJumping();
}

void APlayerBaseCharacter::ChangeAnim(const bool isChange)
{
	isAttackAnim = isChange;
	UCharacterMovementComponent* characterMovement = GetCharacterMovement();
	characterMovement->SetMovementMode(EMovementMode::MOVE_None);
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance) {
		if (!isAttackAnim) {
			AnimInstance->Montage_Play(UnequipAnim);
			SwitchWeaponPoint(FName("WeaponToHandPoint"));
			characterMovement->bUseControllerDesiredRotation = false;
			characterMovement->bOrientRotationToMovement = true;
		}
		else {
			AnimInstance->Montage_Play(EquipAnim);
			characterMovement->bUseControllerDesiredRotation = true;
			characterMovement->bOrientRotationToMovement = false;
		}
	}
}

void APlayerBaseCharacter::PlayAttackInPlayer()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && isAttackAnim) {
		SetCharacterMovement(EMovementMode::MOVE_None);
		int32 randomIndex = FMath::RandRange(0, 4);
		AnimInstance->Montage_Play(AttackAnimList[randomIndex]);
	}
}



void APlayerBaseCharacter::SetCharacterMovement(const EMovementMode movementMode)
{
	GetCharacterMovement()->SetMovementMode(movementMode);
}
void APlayerBaseCharacter::AddHealth(const float addValue)
{
	health += addValue;
	health = health > maxHealth ? maxHealth : health;
}
//攻击检测
void APlayerBaseCharacter::AttackDamage()
{
	FVector startPos = GetActorLocation();
	FVector endPos = startPos + GetActorForwardVector() * 200;
	TArray<AActor*> ignoreActors;
	TArray<FHitResult> hitList;
	bool isResult = UKismetSystemLibrary::SphereTraceMultiByProfile(GetWorld(), startPos, endPos, attackRadius, FName(""), true, ignoreActors, EDrawDebugTrace::ForOneFrame, hitList, true);
	if (isResult) {
		/*for (FHitResult hitRes : hitList) {
			ABaseCharacter* enemy = Cast<AEnemyBaseCharacter>(hitRes.GetActor());
			if (enemy) {
				enemy->TakeHitDamage(20.0f);
			}
		}*/
		TArray<ABaseCharacter*> enemyList = GetAttackRangeEnemy(hitList);
		if (enemyList.Num() > 0) {
			for (ABaseCharacter* enemy : enemyList) {
				enemy->TakeHitDamage(20.0f);
			}
		}
	}
}



TArray<ABaseCharacter*> APlayerBaseCharacter::GetAttackRangeEnemy(const TArray<FHitResult> hitList)
{
	TArray<ABaseCharacter*> RangeEnemyList;
	for (FHitResult hitRes : hitList) {
		ABaseCharacter* enemy = Cast<AEnemyBaseCharacter>(hitRes.GetActor());
		if (enemy) {
			RangeEnemyList.AddUnique(enemy);
		}
		else {
			enemy = Cast<ABossBaseCharacter>(hitRes.GetActor());
			if (enemy) {
				RangeEnemyList.AddUnique(enemy);
			}
		}
	}
	return RangeEnemyList;
}

void APlayerBaseCharacter::PauseGameInput()
{
	GameMode->ShowPausePanel();
}

void APlayerBaseCharacter::RegisterInput()
{
	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (playerController) {
		UEnhancedInputLocalPlayerSubsystem* subSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
		if (subSystem) {
			subSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
void APlayerBaseCharacter::SpawnWeapon()
{
	weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	SwitchWeaponPoint(FName("NormalWeaponPoint"));
}

void APlayerBaseCharacter::SwitchWeaponPoint(FName pointName)
{
	if (weapon) {
		FAttachmentTransformRules attachRules(EAttachmentRule::SnapToTarget, false);
		weapon->AttachToComponent(GetMesh(), attachRules, pointName);
		weapon->SetOwner(this);
	}
}
void APlayerBaseCharacter::HitResponse()
{
	if (GameMode) {
		GameMode->PlayBloodAnimation();
	}
	float rValue = FMath::RandRange(0.0f, 1.0f);
	if (rValue > 0.5f) {
		GetMesh()->GetAnimInstance()->Montage_Play(HitMontage);
	}
}

void APlayerBaseCharacter::DeathResponse()
{
	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (playerController) {
		GameMode->ShowGameOverPanel(FText::FromString("DEFEAT"));
		FInputModeUIOnly uiOnly;
		playerController->SetInputMode(uiOnly);
		playerController->bShowMouseCursor = true;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	}
}
