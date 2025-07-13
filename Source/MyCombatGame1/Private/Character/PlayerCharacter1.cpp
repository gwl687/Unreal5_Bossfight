// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter1.h"
#include "GameFramework/SpringArmComponent.h"//���뵯�ɱ����ͷ�ļ�
#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "KismetAnimationLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Character\Enemy\Boss1Character.h"
#include "NiagaraComponent.h"
#include "Components\CapsuleComponent.h"
#include "OtherBaseActors\AttackActor.h"
#include "Anim\Player\Player1AnimIns.h"

APlayerCharacter1::APlayerCharacter1()
{
	//�����������
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom);
	//����
	weaponComponent = CreateDefaultSubobject<UBoxComponent>("WeaponCollision");
	weaponComponent->SetupAttachment(GetMesh(), "FX_weapon_base");
	weaponComponent->SetCollisionObjectType(ECC_WorldDynamic);
	weaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weaponComponent->SetRelativeLocation(FVector(90.f, 0.f, 0.f));
	weaponComponent->SetBoxExtent(FVector(100.f, 32.f, 32.f));
	weaponComponent->ComponentTags.Add("PlayerAttack");
	//��ɫ��������
	GetCharacterMovement()->BrakingDecelerationWalking = 2048.0f;
	attackDamage = 15;
	//��ת�ٶ�
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 960.0f, 0.0f);
}

void APlayerCharacter1::BeginPlay()
{
	Super::BeginPlay();
	energy = maxEnergy;
	//��ײ��������
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter1::OnCapsuleBeginOverlap);
}

//��ұ���ײ
void APlayerCharacter1::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (1) {
		//����ֱ�ӹ���
		if (OtherComp->ComponentHasTag("EnemyAttack")) {
			TakeHit(Cast<ABaseCharacter>(OtherComp->GetOwner())->attackDamage, OtherComp->GetOwner()->GetActorLocation());
			OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		//�����͹���
		if (OtherComp->ComponentHasTag("ItemAttack")) {
			TakeHit(Cast<AAttackActor>(OtherComp->GetOwner())->attackDamage, OtherComp->GetOwner()->GetActorLocation());
			OtherComp->SetActive(false);
		}
	}
}

void APlayerCharacter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (enterRunningCd) {
		RunningCdCnt += DeltaTime;
	}
	if (enterRAbilityCd) {
		RAbilityCdCnt += DeltaTime;
	}
	if (RunningCdCnt > 3) {
		enterRunningCd = false;
		RunningCdCnt = 0;
	}
	if (RAbilityCdCnt > 3) {
		enterRAbilityCd = false;
		RAbilityCdCnt = 0;
	}
	if (energy < maxEnergy) {
		energy += 10 * DeltaTime;
	}
	if (energy <= 0 && Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning) {
		runningCdState = true;
		enterRunningCd = true;
		InputRunToWalk(true);
	}
	FVector Velocity = GetVelocity();
	Velocity.Z = 0;
	if (Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning && energy > 0) {
		//energy -= 20 * DeltaTime;
	}
	//����R
	if (isAbilityRCharging && energy > 0) {
		//energy -= 35 * DeltaTime;
	}
	if (isAbilityRCharging && energy <= 0) {
		enterRAbilityCd = true;
		RAbilityCdState = true;
		InputAbilityReleaseR();
		//float stopTime = GetMesh()->GetAnimInstance()->Montage_GetPosition(AttackAnimList[5]);
		//GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimList[5], -1, EMontagePlayReturnType::MontageLength, stopTime);
	}
	if (!Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isFalling) {
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isJumpingAttack = false;
	}
	//�ж��Ƿ����ܲ�
	if (isRunning) {
		GetCharacterMovement()->MaxWalkSpeed = 1000;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 600;
	}
	//�ս�
	if (Velocity.Size() > 750 && !isSwordOnBack
		&& !GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) {
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = true;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isSheathSwordEndRunning = true;
		GetMesh()->GetAnimInstance()->Montage_Play(TravelStart);
		isSwordOnBack = true;
	}
	//�ν�
	if (Velocity.Size() < 600 && isSwordOnBack
		&& !GetMesh()->GetAnimInstance()->IsAnyMontagePlaying()) {
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Hello, travelstop!"));
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = true;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isSheathSwordEndRunning = false;
		GetMesh()->GetAnimInstance()->Montage_Play(TravelStop);
		isSwordOnBack = false;
	}
}

//����ƶ�
void APlayerCharacter1::InputMove(const FVector2D axis2D)
{
	if (Controller != nullptr && canMoveAndJump) {
		if (!GetCharacterMovement()->IsFalling()) {
			Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isJumpingState = false;
		}
		FRotator rotation = Controller->GetControlRotation();
		FRotator yawRotation(0.0f, rotation.Yaw, 0.0f);
		//�������ת�Ƕ��£�ǰ���ķ�������
		FVector forwardDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
		FVector rightDir = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(forwardDir, axis2D.X);
		AddMovementInput(rightDir, axis2D.Y);
	}
}

//
void APlayerCharacter1::InputLookRotation(const FVector2D axis2D)
{
	if (Controller != nullptr) {
		AddControllerYawInput(axis2D.X);
		AddControllerPitchInput(axis2D.Y);
	}
}
//�����Ծ
void APlayerCharacter1::InputJump(const bool isJump)
{
	//GetMesh()->GetAnimInstance()->Montage_Play(TravelStart);
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isJumpingState = true;
	isJump ? Jump() : StopJumping();
}
//��shift˲��
void APlayerCharacter1::InputDodge(const bool isDodge)
{
	if (energy >= 40 && canCombo
		&& !Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRolling) {
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = false;
		//energy -= 40;
		//Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
		canCombo = false;
		canMoveAndJump = false;
		GetMesh()->GetAnimInstance()->Montage_Play(StartRolling);
	}
}
//�ܲ�
void APlayerCharacter1::InputRun()
{
	if (energy > 0
		&& !enterRunningCd
		&& !runningCdState
		&& !isSwordOnBack) {
		isRunning = true;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = true;
	}
}
//�ܲ�ת��Ϊ��·
void APlayerCharacter1::InputRunToWalk(bool isInput)
{
	isRunning = false;
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isSheathSwordEndRunning  = false;
	GetMesh()->GetAnimInstance()->Montage_Play(TravelStop);
	/*if (!isInput) {
		runningCdState = false;
	}
	if (!Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning) {
		return;
	}
	if (Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRolling) {
		return;
	}*/
	//if (isRunning) {
	//	isRunning = false;
	//	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
	//	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isTravelEndRunning = false;
	//	if (!Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isJumpingState) {
	//		float stopTime = GetMesh()->GetAnimInstance()->Montage_GetPosition(TravelStart);
	//		float travalMontageLength = TravelStart->GetPlayLength();
	//		//�ν�
	//		GetMesh()->GetAnimInstance()->Montage_Play(TravelStop);
	//		//�ս���û��ɣ���;�ν�
	//		if (stopTime > 0) {
	//			GetMesh()->GetAnimInstance()->Montage_SetPosition(TravelStop, travalMontageLength - stopTime);
	//		}
	//	}
	//}
}
void APlayerCharacter1::RunToWalk()
{
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isTravelEndRunning = false;
}
//�ر�������Ч�ĺ���
void APlayerCharacter1::DeactivatePlayerGhostEffect()
{
	if (PlayerGhostEffect)
	{
		PlayerGhostEffect->SetActive(false);  // ���� SetVisibility(false);
	}
}


//��ɫ����
void APlayerCharacter1::InputPlayerAttack()
{
	if (canCombo && energy >= 25)
	{
		canMoveAndJump = false;
		//Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		//energy -= 25;
		canCombo = false;
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isAttacking = true;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isJumpingState = false;
		if (AnimInstance) {
			AnimInstance->Montage_Play(AttackAnimList[attackIndex]);
			attackIndex = attackIndex < 3 ? attackIndex + 1 : 0;
		}
	}
}


void APlayerCharacter1::InputAbilityR()
{
	if (canCombo && energy > 0 && !GetCharacterMovement()->IsFalling()
		&& !RAbilityCdState && !enterRAbilityCd) {
		canCombo = false;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isAttacking = true;
		if (!isAbilityRCharging && canRechargeR) {
			GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimList[5]);
			isAbilityRCharging = true;
		}
	}
}

void APlayerCharacter1::InputAbilityReleaseR()
{
	RAbilityCdState = false;
	canCombo = false;
	if (isAbilityRCharging) {
		if (!canReleaseR) {
			GetMesh()->GetAnimInstance()->Montage_Stop(0.5f);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, rEnd!"));
			isAbilityRCharging = false;
		}
		else {
			enterRAbilityCd = true;
			ReleaseR();
		}
	}
}

void APlayerCharacter1::ReleaseR()
{
	attackDamage = 2000;
	canRechargeR = false;
	GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimList[6]);
	canReleaseR = false;
	isAbilityRCharging = false;
}

void APlayerCharacter1::rollToRun()
{
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = true;
	//Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = true;
	GetMesh()->GetAnimInstance()->Montage_Play(TravelStart);
}


void APlayerCharacter1::InputAbilityRightButton()
{
	if (canCombo && energy >= 0 && !GetCharacterMovement()->IsFalling()) {
		canMoveAndJump = false;
		GetMesh()->GetAnimInstance()->Montage_Play(AttackAnimList[7]);
		canCombo = false;
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isUpperBodyBlend = false;
		//Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isRunning = false;
		GetCharacterMovement()->MaxWalkSpeed = 600;
		//energy -= 40;
	}
}




//������ͨ��������
void APlayerCharacter1::PlayNormalAttack()
{
	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontageList[0]);
}

void APlayerCharacter1::NormalAttackCollision()
{
	weaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
}

//ʵ����ͨ����ʩ���˺�
void APlayerCharacter1::NormalAttackCollisionCancel()
{
	weaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void APlayerCharacter1::NormalAttackEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, canCombo!"));
	canRechargeR = true;
	attackIndex = 0;
	canCombo = true;
	canMoveAndJump = true;
	attackDamage = 2000;
	Cast<UPlayer1AnimIns>(GetMesh()->GetAnimInstance())->isAttacking = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void APlayerCharacter1::EnterIdleAndMove()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

float APlayerCharacter1::getEnergyProgress()
{
	if (maxEnergy) {
		return energy / maxEnergy;
	}
	return 0.0f;
}

void APlayerCharacter1::HitResponse()
{
}

void APlayerCharacter1::DeathResponse()
{
}

//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Hello, AnimCharacter!"));



