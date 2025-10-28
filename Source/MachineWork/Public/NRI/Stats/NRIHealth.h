// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NRIHealth.generated.h"

/*
	Раны, вроде тут всё понятно, но нужно понимать, что раны этов том числе и крит урон
	У персонажа должено быть число ран, возможность получить крит урон, который может 
	повесить некоторые травмы, которые также будут описанны здесь, также персонаж может иметь 
	возможность быстрой смерти, чтобы пропусть этап с таблицей 

	Таблица будет взята из 2Ериси и крит урон будет накапливатся, пока так. 

	Травмы будут давать штрафы, тут уже нужно будет сложное взаимодействие этого компонента с 
	другими, так как травмы могут лишить персонажа слота под оружие либо скосить характеристики

	Таким образом травмы требывать другие зависимые компоненты подписыватся на их оповещения 
	и както реагировать соотвецтвенно 

	Пример: Получина травматическая ампутация руки, возможность держать оружие в левой руке
		невозможно - ОПОВЕЩАЮ !

	В свою очередь иные компоненты будут иметь виртуальную функцию которой будут подписыватся
	на это оповещение. 
	Или нет, хуй его знает, подумаю ещё 

	==========================================

	Все болие тонкие подробности будут описанны в конкретных компанентах

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
