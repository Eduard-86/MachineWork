// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "NRI/BattleMap/BaseCombatGrid.h"

#include "BaceNRICharacter.generated.h"

//struct FCombatGridCell;

/// <summary>
/// Запихни премещение с оповещениями в отдельный компонент
/// </summary>
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FNRICharMovePathStarted, ABaceNRICharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint, FCombatGridCell, NextPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePointStarted, ABaceNRICharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePointComplite, ABaceNRICharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FNRICharMovePathSComlited, ABaceNRICharacter*, NRIChar,
	FCombatGridCell, StartPoint, FCombatGridCell, FinishPoint);

UCLASS(config=Game)
class ABaceNRICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaceNRICharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

public:

	UFUNCTION()
	void StartMoveToPoints(TArray<FCombatGridCell> PointsArray);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

protected:

	UFUNCTION()
	void MoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
	

};