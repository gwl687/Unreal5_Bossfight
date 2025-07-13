// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "Components\CapsuleComponent.h"
#include "Animation/AnimInstance.h"
#include "Anim\BaseAnimInstance.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	speed = 600;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
}
//受伤(根据敌人方向播放不同受伤动画)
void ABaseCharacter::TakeHit(float damage, FVector AttackerLocation)
{
	UBaseAnimInstance* AnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	health -= damage;
	if (AnimInstance) {
		if (health <= 0) {
			AnimInstance->isDead = true;
			ABaseCharacter::DeathResponse();
		}
		else {
			//Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance())->getHit = true;
			FVector Forward = GetActorForwardVector();
			FVector ToAttacker = (AttackerLocation - GetActorLocation()).GetSafeNormal();
			// 计算夹角
			float AngleDegrees = FMath::RadiansToDegrees(acosf(FVector::DotProduct(Forward, ToAttacker)));
			float CrossZ = FVector::CrossProduct(Forward, ToAttacker).Z;
			TObjectPtr<UAnimMontage> MontageToPlay = nullptr;
			if (AngleDegrees < 45.f)
			{
				MontageToPlay = HitMontageFront;
				Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance())->hitNum = 0;
			}
			else if (AngleDegrees > 135.f)
			{
				MontageToPlay = HitMontageBack;
				Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance())->hitNum = 1;
			}
			else if (CrossZ >  0)
			{
				MontageToPlay = HitMontageRight;
				Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance())->hitNum = 2;
			}
			else
			{
				MontageToPlay = HitMontageLeft;
				Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance())->hitNum = 3;
			}
			if (MontageToPlay)
			{
				PlayAnimMontage(MontageToPlay);
			}
		}
	}
}
//找到攻击范围内的敌人
AActor* ABaseCharacter::GetAttackRangeActor(const TArray<FHitResult> hitList, FName MyTag)
{
	AActor* player = nullptr;
	for (FHitResult hitRes : hitList) {
		player = Cast<ABaseCharacter>(hitRes.GetActor());
		if (player) {
			break;
		}
	}
	return player;
}

float ABaseCharacter::getHealthProgress()
{
	if (maxHealth) {
		return health / maxHealth;
	}
	return 0.0f;
};

void ABaseCharacter::HitResponse()
{
}
//玩家和敌人的死亡响应
void ABaseCharacter::DeathResponse()
{
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//PlayAnimMontage(DeathMontage);
	//GetMesh()->SetAnimInstanceClass(nullptr);
	//执行玩家死亡响应
	if (ActorHasTag("Player")) {
		APlayerController* playerController = Cast<APlayerController>(GetController());
		if (playerController) {
			//GameMode->ShowGameOverPanel(FText::FromString("DEFEAT"));
			FInputModeUIOnly uiOnly;
			playerController->SetInputMode(uiOnly);
			playerController->bShowMouseCursor = true;
		}
	}
	//执行敌人死亡响应
	else {
		//HealthBar->DestroyComponent();
		AAIController* controller = Cast<AAIController>(GetController());
		if (controller) {
			controller->BrainComponent->StopLogic("");
			controller->ClearFocus(EAIFocusPriority::Default);		
			//	ACombatGameMode* gameMode = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
			//	gameMode->RemoveEnemy(this);
			//FTimerHandle TimerHandle;
			//GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseCharacter::DestroySelf, 3.0f, false);
			//MyDelay(3.0f, FName("DestroyEnemy"));
		}
	}
}

void ABaseCharacter::DestroySelf()
{
	Destroy();
}

/*oid ABaseCharacter::MyDelay(float delayTime, FName FunctionName)
{
	FLatentActionInfo actionInfo;
	actionInfo.Linkage = 1;
	actionInfo.UUID = 100;
	actionInfo.CallbackTarget = this;
	actionInfo.ExecutionFunction = FunctionName;
	UKismetSystemLibrary::Delay(GetWorld(), delayTime, actionInfo);
}*/



void ABaseCharacter::AttackDamage()
{
}

void ABaseCharacter::PlayAttack()
{
	//GetMesh()->GetAnimInstance()->Montage_Play(AttackMontageList[0]);
}



