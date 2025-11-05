// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LinearAlgebraFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MACHINEWORK_API ULinearAlgebraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//UFUNCTION(
	//	BlueprintCallable,
	//	BlueprintPure,
	//	Category = "Math | Byte",
	//	meta = (
	//		Keywords = "simona shr >> byte uint8",
	//		DisplayName = "ShiftRight (byte)",
	//		CompactNodeTitle = ">>"
	//		)
	//)
	//static FORCEINLINE uint8 ShiftRight_Uint8(const uint8 Value, const int32 Shift) { return Value >> Shift; }

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "V>>"
			)
	)
	static float VectorLength(FVector vector);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "*"
			)
	)
	static FVector MultiplicationScalar(float scalar, FVector vector);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "/"
			)
	)
	static FVector DivisionScalar(float scalar, FVector vector);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "Norm"
			)
	)
	static FVector VectorNormalization(FVector vector);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "VSum+"
			)
	)
	static FVector VectorSum(FVector vector1, FVector vector2);

	UFUNCTION(
		BlueprintCallable,
		BlueprintPure,
		Category = "VecorMath",
		meta = (
			Keywords = "simona shr >> byte uint8",
			DisplayName = "VShiftRight (byte)",
			CompactNodeTitle = "VDifference-"
			)
	)
	static FVector VectorDifference(FVector vector1, FVector vector2);
};
