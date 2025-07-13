// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boss1Tornado.generated.h"

class UCapsuleComponent;
class USpringArmComponent;

UCLASS()
class MYCOMBATGAME1_API ABoss1Tornado : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoss1Tornado();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* CameraBoom;
	virtual void BeginPlay() override;
	void ActivateCapsule();
	void DeactivateCapsule();
	void StartFadeOut();
	void FadeOut();
public:	
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyProperty")
	float AttackDamage;
};
