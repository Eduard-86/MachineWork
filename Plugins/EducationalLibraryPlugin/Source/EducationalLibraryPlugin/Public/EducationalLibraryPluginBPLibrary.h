// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EducationalLibraryPluginBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UEducationalLibraryPluginBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

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

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static float VectorLength(FVector vector);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static FVector MultiplicationScalar(FVector vector, float scalar);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static FVector DivisionScalar(FVector vector, float scalar);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static FVector VectorNormalization(FVector vector);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static FVector VectorSum(FVector vector1, FVector vector2);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|StandartVecLib", meta = (Keywords = "eduard"))
	static FVector VectorDifference(FVector vector1, FVector vector2);

	// Return speed vector for unit of time
	// If get length we get speed scalar 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|AlgebVecLib", meta = (Keywords = "eduard"))
	static FVector GetSpeedVector(FVector StartPosition, FVector PositionAfterTime, float MoveTime);

	// SpeedDelta can be 0.0 - 1.0
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Math|AlgebVecLib", meta = (Keywords = "eduard"))
	static FVector GetEMAAverageSpeed(FVector SpeedVector, FVector OldEMASpeed, float SpeedDelta);
	
};
