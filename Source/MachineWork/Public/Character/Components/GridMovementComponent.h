// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NRI/BattleMap/BaseCombatGrid.h"

#include "GridMovementComponent.generated.h"


/// <summary>
/// Запихни премещение с оповещениями в отдельный компонент
/// </summary>
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePathStarted, ACharacter*, NRIChar,
	FCellIndex, StartPoint, FCellIndex, FinishPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMoveDelegate, ACharacter*, NRIChar,
	FCellIndex, StartPoint, FCellIndex, FinishPoint);
/*
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePointStarted, ACharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePointComplite, ACharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePathSComlited, ACharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);
	*/
/*
	Перемещаемся
*/


UCLASS(config = Game, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MACHINEWORK_API UGridMovementComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UGridMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

	virtual void PostInitProperties() override;


protected:

	// ну в будущем мб и акторы будут бегать по гриду
	UPROPERTY(BlueprintReadOnly)
	bool IsOwnerChar = true;

	UPROPERTY(BlueprintReadOnly)
	FCellIndex MyGridPointIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Grid")
	FCellIndex StartCell;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, Category = "Grid")
	TObjectPtr<ABaseCombatGrid> OwnerGrid;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:

	UFUNCTION()
	void MoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

	//void StartMoveToPoint();


protected:

	//TArray<FCombatGridCell> GridPath;

	TArray<FCellIndex> GridPathIndex;

	uint8 PathCounter = 0;


	TObjectPtr<AAIController> OwnAICont;

	TObjectPtr<ACharacter> OwnChar;

public:

	UPROPERTY(BlueprintAssignable, Category = "MoveDelegate")
	FNRICharMoveDelegate StartMoveToPoint;
	UPROPERTY(BlueprintAssignable, Category = "MoveDelegate")
	FNRICharMoveDelegate CompleteMoveToPoint;
	UPROPERTY(BlueprintAssignable, Category = "MoveDelegate")
	FNRICharMovePathStarted StartMoveToPath;
	UPROPERTY(BlueprintAssignable, Category = "MoveDelegate")
	FNRICharMoveDelegate CompleteMoveToPath;

public:

	UFUNCTION(BlueprintCallable)
	bool StartMoveToGrid(TArray<FCellIndex> IndexPathArray);

};
