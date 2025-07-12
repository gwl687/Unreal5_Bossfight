// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "DebugHelper.h"

// Sets default values
AMyActor::AMyActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	/*UE_LOG(LogTemp, Warning, TEXT("RUN A AActor BeginPlay"));

	GEngine->AddOnScreenDebugMessage(-1, 5, FColor::MakeRandomColor(),FString(TEXT("Hello C++")));*/
	Debug::Print("Run DebugHelper Message", FColor::White,5.0f);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

