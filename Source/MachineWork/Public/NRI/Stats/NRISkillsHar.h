// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "Components/ActorComponent.h"
#include "NRI/Stats/Base_NRIProperty.h"
#include "NRISkillsHar.generated.h"

/*
	Ќу давай по пор€дку, что мы хотим.
	√лавна€ цель это дать персонажу набор характеристик известных заранее.
	»звестен именно набор а не значени€. 

	==============

	¬се болие тонкие подробности будут описанны в конкретных компанентах

*/

USTRUCT(BlueprintType)
struct MACHINEWORK_API FMainProfileCharacteristics
{
	GENERATED_BODY()

	//UPROPERTY(ClampMin = "0", ClampMax = "100")
	UPROPERTY(DisplayName = "WS", BlueprintReadWrite)
		int32 WeaponSkill = 0;

	UPROPERTY(DisplayName = "BS", BlueprintReadWrite)
		int32 BallisticSkill = 0;

	UPROPERTY(DisplayName = "S", BlueprintReadWrite)
		int32 Strength = 0;

	UPROPERTY(DisplayName = "T", BlueprintReadWrite)
		int32 Toughness = 0;

	UPROPERTY(DisplayName = "Ag", BlueprintReadWrite)
		int32 Agility = 0;

	UPROPERTY(DisplayName = "Int", BlueprintReadWrite)
		int32 Intelligence = 0;

	UPROPERTY(DisplayName = "WP", BlueprintReadWrite)
		int32 WillPower = 0;

	UPROPERTY(DisplayName = "Fel", BlueprintReadWrite)
		int32 Fellowship = 0;
};

USTRUCT(BlueprintType)
struct FSecondaryProfileCharacteristics
{
	GENERATED_BODY()

		//UPROPERTY(ClampMin = "0", ClampMax = "100")
	UPROPERTY(DisplayName = "A")
		int32 Attacks = 0;

	UPROPERTY(DisplayName = "W")
		int32 Wounds = 0;

	UPROPERTY(DisplayName = "BS")
		int32 StrengthBonus = 0;

	UPROPERTY(DisplayName = "BT")
		int32 ToughnessBonus = 0;

	UPROPERTY(DisplayName = "M")
		int32 Movement = 0;

	UPROPERTY(DisplayName = "Mag")
		int32 Magic = 0;

	UPROPERTY(DisplayName = "IP")
		int32 InsanityPoints = 0;

	UPROPERTY(DisplayName = "FP")
		int32 FatePoints = 0;
};


UCLASS(config = Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MACHINEWORK_API UNRISkillsHar : public UBase_NRIProperty
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UNRISkillsHar();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite)
	FMainProfileCharacteristics MainCharacterictics;

	UPROPERTY(BlueprintReadWrite)
	FSecondaryProfileCharacteristics SecondCharacterictics;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
