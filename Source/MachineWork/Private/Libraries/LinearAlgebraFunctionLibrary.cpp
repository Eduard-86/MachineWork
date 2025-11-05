// Fill out your copyright notice in the Description page of Project Settings.


#include "Libraries/LinearAlgebraFunctionLibrary.h"
#include "Math/UnrealMathUtility.h"

float ULinearAlgebraFunctionLibrary::VectorLength(FVector vector)
{
	// Корень
	// FMath::Sqrt(10.f);

	// Степень 
	// FMath::Pow(6.f, 2.f);

	float SumPow = FMath::Pow(vector.X, 2.f) + FMath::Pow(vector.Y, 2.f) + FMath::Pow(vector.Z, 2.f);

	return FMath::Sqrt(
		FMath::Pow(vector.X, 2.f) +
		FMath::Pow(vector.Y, 2.f) +
		FMath::Pow(vector.Z, 2.f));
}

FVector ULinearAlgebraFunctionLibrary::MultiplicationScalar(float scalar, FVector vector)
{
	return FVector(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

FVector ULinearAlgebraFunctionLibrary::DivisionScalar(float scalar, FVector vector)
{
	return FVector(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

FVector ULinearAlgebraFunctionLibrary::VectorNormalization(FVector vector)
{
	float temp = 1.f / VectorLength(vector);

	return MultiplicationScalar(temp, vector);
}

FVector ULinearAlgebraFunctionLibrary::VectorSum(FVector vector1, FVector vector2)
{
	return FVector(
		vector1.X + vector2.X,
		vector1.Y + vector2.Y,
		vector1.Z + vector2.Z);
}

FVector ULinearAlgebraFunctionLibrary::VectorDifference(FVector vector1, FVector vector2)
{
	return FVector(
		vector1.X - vector2.X,
		vector1.Y - vector2.Y,
		vector1.Z - vector2.Z);
}
