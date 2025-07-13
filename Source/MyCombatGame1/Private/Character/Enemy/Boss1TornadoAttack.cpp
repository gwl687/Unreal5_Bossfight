// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Boss1TornadoAttack.h"
#include "Components\CapsuleComponent.h"

ABoss1TornadoAttack::ABoss1TornadoAttack()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetupAttachment(RootComponent);
}

void ABoss1TornadoAttack::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle activeHandler;
	GetWorld()->GetTimerManager().SetTimer(activeHandler, this, &ABoss1TornadoAttack::ActivateCapsule, 1.0f, true);
}

void ABoss1TornadoAttack::ActivateCapsule()
{
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//Ò»Ö¡ºó½ûÓÃÅö×²
	FTimerHandle DisableHandle;
	float FrameTime = GetWorld()->GetDeltaSeconds();
	GetWorld()->GetTimerManager().SetTimer(DisableHandle, this, &ABoss1TornadoAttack::DeactivateCapsule, FrameTime, false);
}

void ABoss1TornadoAttack::DeactivateCapsule()
{
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


