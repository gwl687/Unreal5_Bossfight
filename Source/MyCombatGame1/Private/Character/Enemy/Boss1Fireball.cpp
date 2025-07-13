// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Boss1Fireball.h"

// Sets default values
ABoss1Fireball::ABoss1Fireball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoss1Fireball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoss1Fireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

