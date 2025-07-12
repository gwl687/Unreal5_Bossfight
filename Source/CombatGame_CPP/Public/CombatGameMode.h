// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CombatGameMode.generated.h"

class UUserWidget;
class UMainUIWidget;
class AEnemyBaseCharacter;
class ABossBaseCharacter;
class UPauseWidget;
class AAudioActor;
/**
 *
 */
UCLASS()
class COMBATGAME_CPP_API ACombatGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACombatGameMode();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> MainUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> GameOverUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseUIClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TSubclassOf<AAudioActor> AudioActorClass;
	UPROPERTY(BlueprintReadOnly, Category = "UIWidget")
	UMainUIWidget* MainUI;
	UPROPERTY(BlueprintReadOnly, Category = "CreatePoint")
	TArray<AActor*> CreatePointList;
	UPROPERTY(EditAnywhere, Category = "EnemyClass")
	TArray<TSubclassOf<AEnemyBaseCharacter>> EnemyClassList;
	UPROPERTY(BlueprintReadOnly, Category = "CreatePoint")
	TArray<AEnemyBaseCharacter*> EnemyList;
	UPROPERTY(BlueprintReadOnly, Category = "CreateNumber")
	int32 CreateNum = 0;
	UPROPERTY(BlueprintReadOnly, Category = "CreateNumber")
	bool IsCreateBoss = true;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BossClass")
	TSubclassOf<ABossBaseCharacter> BossClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BossClass")
	TObjectPtr<UPauseWidget> PauseWidget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	TObjectPtr<AAudioActor> AudioActor;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void LoopCreateEnemy();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void CreateBoss();
public:
	UPROPERTY(BlueprintReadOnly, Category = "CreatePoint")
	AActor* BossCreatePoint;
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void PlayBloodAnimation();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void AddPointToList(AActor* point);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void BeginCreateEnemy();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void RemoveEnemy(AEnemyBaseCharacter* enemy);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void HideBossHealthBar();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void ShowGameOverPanel(FText desText);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void ShowPausePanel();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void HidePausePanel();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void RestartGame();
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void OnVolumeValueChange(float value);
	UFUNCTION(BlueprintCallable, Category = "MyFunction")
	void OnMusicPaused(bool isOn);
};
