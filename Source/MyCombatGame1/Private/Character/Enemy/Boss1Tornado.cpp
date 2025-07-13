// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Boss1Tornado.h"
#include "Components\CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Character\BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABoss1Tornado::ABoss1Tornado()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>("SceneRoot");
	RootComponent = SceneRoot;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>("CapsuleComponent");
	CapsuleComponent->SetupAttachment(RootComponent);
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABoss1Tornado::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle activeHandler;
	GetWorld()->GetTimerManager().SetTimer(activeHandler, this, &ABoss1Tornado::ActivateCapsule, 1.0f, true);
	GetWorldTimerManager().SetTimer(activeHandler, this, &ABoss1Tornado::StartFadeOut, 5.0f, false);
}


void ABoss1Tornado::ActivateCapsule()
{
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//一帧后禁用碰撞
	FTimerHandle DisableHandle;
	float FrameTime = GetWorld()->GetDeltaSeconds();
	GetWorld()->GetTimerManager().SetTimer(DisableHandle, this, &ABoss1Tornado::DeactivateCapsule, FrameTime, false);
}

void ABoss1Tornado::DeactivateCapsule()
{
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ABoss1Tornado::StartFadeOut()
{
	// 每帧淡出（比如每 0.05 秒）
	FTimerHandle FadeTickHandle;
	GetWorldTimerManager().SetTimer(FadeTickHandle, this, &ABoss1Tornado::FadeOut, 0.05f, true);
}

void ABoss1Tornado::FadeOut()
{
	//CurrentFadeTime += 0.05f;
	//float Alpha = FMath::Clamp(1.0f - CurrentFadeTime / TotalFadeDuration, 0.0f, 1.0f);

	//if (DynamicMaterial)
	//{
	//	DynamicMaterial->SetScalarParameterValue("Opacity", Alpha);
	//}

	//if (Alpha <= 0.0f)
	//{
	//	GetWorldTimerManager().ClearTimer(FadeTickHandle);
	//	Destroy(); // 或 SetActorHiddenInGame(true);
	//}
}

// Called every frame
void ABoss1Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

