// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "BaseCombatGrid.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FCellIndex
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 row;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	uint8 column;

	FCellIndex()
	: row(0), column(0)
	{}

	FCellIndex(uint8 rowinit, uint8 columninit)
		: row(rowinit), column(columninit)
	{}

	FCellIndex(const FCellIndex& other)
		: FCellIndex(other.row, other.column)
	{}

	bool operator==(const FCellIndex& other) const
	{
		return other.row == this->row &&
			other.column == this->column;
	}

	FCellIndex operator+(const FCellIndex& other) const
	{
		return FCellIndex(other.row + this->row,
			other.column + this->column);
	}
	
};

#if UE_BUILD_DEBUG
uint32 GetTypeHash(const FPairGrid& Explain);
#else // optimize by inlining in shipping and development builds
FORCEINLINE uint32 GetTypeHash(const FCellIndex& Explain) {
	uint32 Hash = FCrc::MemCrc32(&Explain, sizeof(FCellIndex));
	return Hash;
}
#endif

USTRUCT(BlueprintType)
struct FCombatGridCell
{
	GENERATED_BODY()

	UPROPERTY()
	FCellIndex index;

	UPROPERTY()
	FVector location;

	UPROPERTY()
	uint8 passability;

	FCombatGridCell()
		: index (FCellIndex(0,0))
		, location(FVector::Zero())
		, passability(0)
	{}

	FCombatGridCell(FCellIndex cellindex, FVector celllocation, uint8 pass)
		: index(FCellIndex(cellindex))
		, location(celllocation)
		, passability(pass)
	{}

	FCombatGridCell(const FCombatGridCell& other)
		: FCombatGridCell(
			other.index
			, other.location
			, other.passability)
	{}

	bool operator==(const FCombatGridCell& other) const
	{
		return other.passability == this->passability;
	}

	bool operator<(const FCombatGridCell& other) const
	{
		return this->passability < other.passability;
	}

};



UCLASS(config = Game)
class MACHINEWORK_API ABaseCombatGrid : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties  Wardruna - Lyfjaberg (Extended)
	ABaseCombatGrid();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UBoxComponent> GridBox;

protected:

	bool IsPrint;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	float DefaultCellSize = 10.f;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly)
	FColor ColorCell = FColor::Blue;

	uint8 GridRow;

	uint8 GridColumn;



public:

	UFUNCTION(CallInEditor, BlueprintCallable)
	void CallInEditorDraeCellBoxes();

	UFUNCTION(CallInEditor, BlueprintCallable)
	void PrintCell();

	void DrawCellBoxes(float CellSize = 10.f, FColor CellColor = FColor::Blue, 
		float TimeVisible = 5);

	void CalculateCells(float CellSize = 10.f, FColor CellColor = FColor::Blue);

public:

	UFUNCTION(BlueprintCallable)
	FVector GetCellLocation(FCellIndex CellIndex);

	UFUNCTION(BlueprintCallable)
	FCombatGridCell GetCell(FCellIndex CellIndex);

	UFUNCTION(BlueprintCallable)
	FCellIndex GetGridSize();


	UFUNCTION(BlueprintCallable)
	FCellIndex FindCellUsingVector(FVector FindLocation);

protected:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void FindPath(FCellIndex StartCell, FCellIndex FinishCell, TArray<FCellIndex>& Path);

protected:

	TMap<FCellIndex, FCombatGridCell> CellsMap;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

