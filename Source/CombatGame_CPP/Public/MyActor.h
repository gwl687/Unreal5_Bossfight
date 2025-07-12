// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()//告诉虚幻引擎生成类的反射数据
class COMBATGAME_CPP_API AMyActor : public AActor//添加的C++类名部分
{
	GENERATED_BODY()//表示当前这个类不直接使用父类的构造函数
	
public:	//当前类的公有模块，外界可以直接访问
	// Sets default values for this actor's properties
	AMyActor();//当前类的构造函数

protected://当前类的受限制模块，外界不能直接访问，子类可以访问
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //在运行时，开始时执行一次

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; //系统方法，实时执行,deltaTime两次执行tick的间隔时间
private://私有模块，外界不能访问，子类也不可访问

};
