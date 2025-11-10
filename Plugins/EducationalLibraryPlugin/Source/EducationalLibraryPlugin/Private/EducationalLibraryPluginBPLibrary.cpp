// Copyright Epic Games, Inc. All Rights Reserved.

#include "EducationalLibraryPluginBPLibrary.h"
#include "EducationalLibraryPlugin.h"
#include "Math/UnrealMathUtility.h"

UEducationalLibraryPluginBPLibrary::UEducationalLibraryPluginBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UEducationalLibraryPluginBPLibrary::VectorLength(FVector vector)
{
	// 
	// FMath::Sqrt(10.f);

	// 
	// FMath::Pow(6.f, 2.f);

	if (vector.IsZero())
		return 0.f;

	float SumPow = FMath::Pow(vector.X, 2.f) + FMath::Pow(vector.Y, 2.f) + FMath::Pow(vector.Z, 2.f);

	return FMath::Sqrt(
		FMath::Pow(vector.X, 2.f) +
		FMath::Pow(vector.Y, 2.f) +
		FMath::Pow(vector.Z, 2.f));
}

FVector UEducationalLibraryPluginBPLibrary::MultiplicationScalar(FVector vector, float scalar)
{
	return FVector(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

FVector UEducationalLibraryPluginBPLibrary::DivisionScalar(FVector vector, float scalar)
{
	if(vector.IsZero())
		return FVector::ZeroVector;

	return FVector(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

FVector UEducationalLibraryPluginBPLibrary::VectorNormalization(FVector vector)
{
	if (vector.IsZero())
		return FVector::ZeroVector;

	float temp = 1.f / VectorLength(vector);

	return MultiplicationScalar(vector, temp);
}

FVector UEducationalLibraryPluginBPLibrary::VectorSum(FVector vector1, FVector vector2)
{
	return FVector(
		vector1.X + vector2.X,
		vector1.Y + vector2.Y,
		vector1.Z + vector2.Z);
}

FVector UEducationalLibraryPluginBPLibrary::VectorDifference(FVector vector1, FVector vector2)
{
	return FVector(
		vector1.X - vector2.X,
		vector1.Y - vector2.Y,
		vector1.Z - vector2.Z);
}

FVector UEducationalLibraryPluginBPLibrary::GetSpeedVector(FVector StartPosition, FVector PositionAfterTime,
	float MoveTime)
{
	// Делим вектор на время за которое было пройденно время
	// чтобы получить дистанцию за еденицу временни
	// был пройден путь в 100 за 2 еденицы времени "сек, мин, час"
	// деля вектор на время мы получаем скорост в еденицу "сек, мин, час"

	return DivisionScalar(StartPosition - PositionAfterTime, MoveTime);
}

FVector UEducationalLibraryPluginBPLibrary::GetEMAAverageSpeed(FVector SpeedVector, FVector OldEMASpeed, float SpeedDelta)
{
	// Мы берём долю от прошлой скорости скорости и прибовляем к нынешней
	// Получая среднюю скорость

	return
		MultiplicationScalar(OldEMASpeed, SpeedDelta) +
		MultiplicationScalar(SpeedVector, (1.f - SpeedDelta));

}
