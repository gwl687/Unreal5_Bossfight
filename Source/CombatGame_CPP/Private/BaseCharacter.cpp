// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "DebugHelper.h"
#include "string"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;
}

void ABaseCharacter::MyDelay(float delayTime,FName FunctionName)
{
	FLatentActionInfo actionInfo;
	actionInfo.Linkage = 1;
	actionInfo.UUID = 100;
	actionInfo.CallbackTarget = this;
	actionInfo.ExecutionFunction = FunctionName;
	UKismetSystemLibrary::Delay(GetWorld(),delayTime,actionInfo);
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::AttackDamage()
{

}

void ABaseCharacter::TakeHitDamage(const float damageValue)
{
	if (health > 0) {
		health -= damageValue;
		if (health <= 0) {
			health = 0;
			DeathResponse();//Ö´ÐÐËÀÍöÏìÓ¦
		}
		else {
			HitResponse();//Ö´ÐÐÉËº¦ÏìÓ¦
		}
	}
}

void ABaseCharacter::HitResponse()
{
	GetMesh()->GetAnimInstance()->Montage_Play(HitMontage);
}

void ABaseCharacter::DeathResponse()
{
}

void ABaseCharacter::PlayAttack()
{
}

