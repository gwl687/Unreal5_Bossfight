// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "DebugHelper.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidget.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PlayerBaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "CombatGameMode.h"
#include "Particles/ParticleSystem.h"
#include "HealthPack.h"

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(RootComponent);
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	//创建控件，并将控件赋值给控件组件
	UHealthBarWidget* healthBarWidget = CreateWidget<UHealthBarWidget>(GetWorld(), HealthBarWidgetClass);
	HealthBar->SetWidget(healthBarWidget);//将血条赋值给控件组件
	healthBarWidget->ownerCharacter = this;//设置ownerCharacter
}

void AEnemyBaseCharacter::DestroyEnemy()
{
	if (DeathParticle) {
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathParticle, GetActorTransform());
	}
	if (HealthPackClass) {
		GetWorld()->SpawnActor<AHealthPack>(HealthPackClass, GetActorTransform());
	}
	Destroy();
}

void AEnemyBaseCharacter::DeathResponse()
{
	HealthBar->DestroyComponent();
	AEnemyAIController* controller = Cast<AEnemyAIController>(GetController());
	if (controller) {
		controller->BrainComponent->StopLogic("");
		controller->ClearFocus(EAIFocusPriority::Default);
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ACombatGameMode* gameMode = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		gameMode->RemoveEnemy(this);
		MyDelay(3.0f, FName("DestroyEnemy"));
	}
}

void AEnemyBaseCharacter::HitResponse()
{
	Super::HitResponse();
	if (!isDamage) {
		isDamage = true;
		AEnemyAIController* controller = Cast<AEnemyAIController>(GetController());
		if (controller) {
			controller->SetAIDamage();
		}
	}
}

void AEnemyBaseCharacter::PlayAttack()
{
	isAttacking = true;
	GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage);
}


void AEnemyBaseCharacter::AttackDamage()
{
	FVector start = GetActorLocation();
	FVector end = start + GetActorForwardVector() * 200;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
	TArray<AActor*> ignoreList;
	TArray<FHitResult> hitList;
	bool isResult = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), start, end, 50.0f, ObjectTypes, true, ignoreList, EDrawDebugTrace::ForOneFrame, hitList, true);
	if (isResult) {
		APlayerBaseCharacter* player = GetAttackRangePlayer(hitList);
		if (player) {
			player->TakeHitDamage(10.0f);
		}
	}
}

APlayerBaseCharacter* AEnemyBaseCharacter::GetAttackRangePlayer(const TArray<FHitResult> hitList)
{
	APlayerBaseCharacter* player = nullptr;
	for (FHitResult hitRes : hitList) {
		player = Cast<APlayerBaseCharacter>(hitRes.GetActor());
		if (player) {
			break;
		}
	}
	return player;
}