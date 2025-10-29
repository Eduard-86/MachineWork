// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseCombatGrid.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FPairGrid
{
	GENERATED_BODY()

	uint8 row;
	uint8 column;

	FPairGrid()
	: row(0), column(0)
	{}

	FPairGrid(uint8 rowinit, uint8 columninit)
		: row(rowinit), column(columninit)
	{}

	FPairGrid(const FPairGrid& other)
		: FPairGrid(other.row, other.column)
	{}

	bool operator==(const FPairGrid& other) const
	{
		return other.row == this->row &&
			other.column == this->column;
	}
	
};

FORCEINLINE uint32 GetTypeHash(const FPairGrid& Explain) {
	uint32 Hash = FCrc::MemCrc32(&Explain, sizeof(FPairGrid));
	return Hash;
}

using CellIndex = TSharedPtr<FPairGrid>;

UCLASS(config = Game)
class MACHINEWORK_API ABaseCombatGrid : public AActor
{
	GENERATED_BODY()

	// TI - target interest | tochka interesa

public:	
	// Sets default values for this actor's properties
	ABaseCombatGrid();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> GridBox;

protected:

	bool IsPrint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DefaultCellSize = 10.f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColor ColorCell = FColor::Blue;

public:

	UFUNCTION(CallInEditor, BlueprintCallable)
	void CallInEditorDraeCellBoxes();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void PrintCell();

	void DrawCellBoxes(float CellSize = 10.f, FColor CellColor = FColor::Blue, 
		float TimeVisible = 5);

	void CalculateCells(float CellSize = 10.f, FColor CellColor = FColor::Blue,
		float TimeVisible = 5);

protected:

	void FindPath(CellIndex StartCell, CellIndex FindCell, TArray<CellIndex> Path);

protected:

	TMap<FPairGrid, FVector> CellsMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
