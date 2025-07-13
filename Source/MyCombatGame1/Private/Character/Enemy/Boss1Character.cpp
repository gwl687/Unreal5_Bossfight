// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Boss1Character.h"
#include "Kismet/GameplayStatics.h"
#include "Character/PlayerCharacter1.h"
#include "Engine/EngineTypes.h"
#include "Components\BoxComponent.h"
#include "Anim\Enemy\Boss1AnimInstance.h"
#include "Components\CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ABoss1Character::ABoss1Character()
{
	leftWeaponComponent = CreateDefaultSubobject<UBoxComponent>("LeftWeaponCollision");
	leftWeaponComponent->SetupAttachment(GetMesh(), "FX_Weapon_L_Base");
	leftWeaponComponent->SetCollisionObjectType(ECC_WorldDynamic);
	leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	leftWeaponComponent->SetBoxExtent(FVector(50.f, 80.f, 50.f));
	rightWeaponComponent = CreateDefaultSubobject<UBoxComponent>("RightWeaponCollision");
	rightWeaponComponent->SetupAttachment(GetMesh(), "FX_Weapon_R_Base");
	rightWeaponComponent->SetCollisionObjectType(ECC_WorldDynamic);
	rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	rightWeaponComponent->SetBoxExtent(FVector(40.f, 80.f, 80.f));
	//Property
	speed = 600;
}



void ABoss1Character::BeginPlay()
{
	Super::BeginPlay();
	//初始化碰撞监听
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ABoss1Character::OnCapsuleBeginOverlap);
}
//碰撞设置
void ABoss1Character::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//玩家直接攻击
	if (OtherComp->ComponentHasTag("PlayerAttack")) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("bossgethit!"));
		TakeHit(Cast<ABaseCharacter>(OtherComp->GetOwner())->attackDamage, OtherComp->GetOwner()->GetActorLocation());
		OtherComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	//道具型攻击
	if (OtherComp->ComponentHasTag("PlayerItemAttack")) {
		/*TakeHit(Cast<AAttackActor>(OtherComp->GetOwner())->attackDamage, OtherComp->GetOwner()->GetActorLocation());
		OtherComp->SetActive(false);*/
	}
}
void ABoss1Character::Tick(float DeltaSeconds)
{
	if (canMove) {
		GetCharacterMovement()->MaxWalkSpeed = speed;
	}
	else {
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}
}
//播放Boss1普通攻击动画
void ABoss1Character::PlayMontage(int Num)
{
	//GetMesh()->GetAnimInstance()->Montage_Play(AttackMontageList[Num], 1.0f, EMontagePlayReturnType::MontageLength, 0.0f);
}

//普通攻击
void ABoss1Character::NormalAttack(float dot)
{
	canMove = false;
	if (dot > cos(70)) {
		GetMesh()->GetAnimInstance()->Montage_Play(attackRight);
	}
	else {
		GetMesh()->GetAnimInstance()->Montage_Play(attackLeft);
	}
}

void ABoss1Character::NormalAttackLeft()
{
	leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABoss1Character::NormalAttackLeftEnd()
{
	leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoss1Character::NormalAttackRight()
{
	GetMesh()->GetAnimInstance()->Montage_Play(attackRight);
	rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ABoss1Character::NormalAttackRightEnd()
{
	rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoss1Character::NormalAttackEnd()
{
	rightWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance())->normalAttack1 = false;
}


void ABoss1Character::NormalAttack2()
{
	leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance())->normalAttack2 = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Boss1LeftAttack"));
}

void ABoss1Character::NormalAttack2End()
{
	leftWeaponComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Cast<UBoss1AnimInstance>(GetMesh()->GetAnimInstance())->normalAttack2 = false;
}

//Boss1技能1
void ABoss1Character::TornadoAttack()
{
	canMove = false;
	GetMesh()->GetAnimInstance()->Montage_Play(skill1);
	FVector TornadoLocation = GetActorLocation() + GetActorForwardVector() * 200;
	FVector SpawnLocation = FVector(TornadoLocation.X, TornadoLocation.Y, 0);
	FRotator SpawnRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(TornadoPrefab, SpawnLocation, SpawnRotation, SpawnParams);
}

void ABoss1Character::TornadoAttackEnd()
{

}

void ABoss1Character::FireballAttack()
{
	FVector MyLocation = GetActorLocation();
	FVector TornadoLocation = FVector(GetActorLocation().X + 15, GetActorLocation().Y, 0);
	FRotator TornadoRotation = FRotator::ZeroRotator;
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(TornadoPrefab, TornadoLocation, TornadoRotation, SpawnParams);
}


