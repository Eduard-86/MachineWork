// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NRIHealth.generated.h"

/*
	����, ����� ��� �� �������, �� ����� ��������, ��� ���� ���� ��� ����� � ���� ����
	� ��������� ������� ���� ����� ���, ����������� �������� ���� ����, ������� ����� 
	�������� ��������� ������, ������� ����� ����� �������� �����, ����� �������� ����� ����� 
	����������� ������� ������, ����� �������� ���� � �������� 

	������� ����� ����� �� 2����� � ���� ���� ����� ������������, ���� ���. 

	������ ����� ������ ������, ��� ��� ����� ����� ������� �������������� ����� ���������� � 
	�������, ��� ��� ������ ����� ������ ��������� ����� ��� ������ ���� ������� ��������������

	����� ������� ������ ��������� ������ ��������� ���������� ������������ �� �� ���������� 
	� ����� ����������� ������������� 

	������: �������� �������������� ��������� ����, ����������� ������� ������ � ����� ����
		���������� - �������� !

	� ���� ������� ���� ���������� ����� ����� ����������� ������� ������� ����� ������������
	�� ��� ����������. 
	��� ���, ��� ��� �����, ������� ��� 

	==========================================

	��� ����� ������ ����������� ����� �������� � ���������� �����������

*/


USTRUCT(BlueprintType)
struct MACHINEWORK_API FInjury
{
	GENERATED_BODY()

		FName InjuryName;

};

UCLASS(config = Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MACHINEWORK_API UNRIHealth : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNRIHealth();

protected:

	int32 Health = 0;

	TArray<FInjury> MyInjury;

	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	int32 GetHealth() { return Health; }
};
