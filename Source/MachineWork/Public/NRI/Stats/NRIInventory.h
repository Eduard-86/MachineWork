// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NRIInventory.generated.h"

/*
	Ну давай по порядку, что мы хотим.
	Цель данного компонента - Предоставить персонажу слоты под экипировку 
	Виды возможной экипировки 

	============================

	*Броня 
		Шлем, Торс, Руки, Ноги 

	*Оружие 
		Занимающее одну руку - меч, щит, нож
		Занимающее обе руки - Секира, лук 

	*Расходники
		Неодгранниченное число типов расходники 
		
	*Походное снаряжение 
		Отдельный массив с вещами в списке 

	============================

	Весь эквик будет ограничиваться по весу 

	============================

	Тип хранения всего эквипа 
	На данный момент я скланяюсь с пециально выделенным структурам под каждый тип инвертаря
	Структура которая будет помещаться в статический массив каждый их которых был создан 
	под каждый тип инвентаря. 
	Массив структур оружия под доспех, массив под оружие, массив под слоты расходников 
	
	Структура будет включать в себя параметры соотвецтвующие типу снарядения
		* Оружие - Урон, Вес, Занимаемые руки, Особенности, Название, Моделька 
		* Броня - Очки защиты, Тип, Вес, Особенности, Название, Какойтовизуал
		* Расходник - Тип, ОчкиЭффекта, Название, Вес, Визуал 
	
	Вес надетого на персонажа эквипа будет отдельной 


*/


UCLASS(config = Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MACHINEWORK_API UNRIInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNRIInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
