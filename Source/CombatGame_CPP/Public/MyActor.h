// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()//�����������������ķ�������
class COMBATGAME_CPP_API AMyActor : public AActor//��ӵ�C++��������
{
	GENERATED_BODY()//��ʾ��ǰ����಻ֱ��ʹ�ø���Ĺ��캯��
	
public:	//��ǰ��Ĺ���ģ�飬������ֱ�ӷ���
	// Sets default values for this actor's properties
	AMyActor();//��ǰ��Ĺ��캯��

protected://��ǰ���������ģ�飬��粻��ֱ�ӷ��ʣ�������Է���
	// Called when the game starts or when spawned
	virtual void BeginPlay() override; //������ʱ����ʼʱִ��һ��

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override; //ϵͳ������ʵʱִ��,deltaTime����ִ��tick�ļ��ʱ��
private://˽��ģ�飬��粻�ܷ��ʣ�����Ҳ���ɷ���

};
