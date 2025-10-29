// Fill out your copyright notice in the Description page of Project Settings.

#include "NRI/BattleMap/BaseCombatGrid.h"

#include "MeshPaintVisualize.h"
#include "Components/BoxComponent.h"


#if UE_BUILD_DEBUG
Fuint32 GetTypeHash(const FPairGrid& Explain) {
	uint32 Hash = FCrc::MemCrc32(&Explain, sizeof(FPairGrid));
	return Hash;
}
#endif

// Sets default values
ABaseCombatGrid::ABaseCombatGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GridBox = CreateDefaultSubobject<UBoxComponent>("LeftHandPoint");
	GridBox->SetupAttachment(RootComponent);
	
}

void ABaseCombatGrid::CallInEditorDraeCellBoxes()
{
	CalculateCells(DefaultCellSize, ColorCell, 20);

	//DrawCellBoxes(DefaultCellSize, ColorCell, 20);
}

void ABaseCombatGrid::PrintCell()
{
	IsPrint = !IsPrint;
}

void ABaseCombatGrid::DrawCellBoxes(float CellSize, FColor CellColor, 
                                    float TimeVisible)
{
	FVector GridBoxScaleVector = GridBox->GetUnscaledBoxExtent();
	FVector BoxLoc = GridBox->GetComponentLocation();

	int CellNumX = (GridBoxScaleVector.X) / CellSize;
	int CellNumY = (GridBoxScaleVector.Y) / CellSize;

	float YCellLoc;
	float FullCellSize = CellSize * 2;


	for (int i = 0; i < CellNumY; i++)
	{
		float XCellLoc;
		YCellLoc = GridBoxScaleVector.Y * -1 + (CellSize + (FullCellSize * i));

		for (int j = 0; j < CellNumX; j++)
		{
			XCellLoc = GridBoxScaleVector.X * -1 + (CellSize + (FullCellSize * j));

			DrawDebugBox(GetWorld(), FVector(BoxLoc.X + XCellLoc, BoxLoc.Y + YCellLoc, BoxLoc.Z),
				FVector(CellSize, CellSize, GridBoxScaleVector.Z), CellColor, false, TimeVisible);
		}
	}
}

void ABaseCombatGrid::CalculateCells(float CellSize, FColor CellColor,
	float TimeVisible)
{
	FVector GridBoxScaleVector = GridBox->GetUnscaledBoxExtent();
	FVector BoxLoc = GridBox->GetComponentLocation();

	int CellNumX = (GridBoxScaleVector.X) / CellSize;
	int CellNumY = (GridBoxScaleVector.Y) / CellSize;

	float YCellLoc;
	float FullCellSize = CellSize * 2;


	for (int i = 0; i < CellNumY; i++)
	{
		float XCellLoc;
		YCellLoc = GridBoxScaleVector.Y * -1 + (CellSize + (FullCellSize * i));

		for (int j = 0; j < CellNumX; j++)
		{
			XCellLoc = GridBoxScaleVector.X * -1 + (CellSize + (FullCellSize * j));

			CellsMap.Add(FPairGrid(i, j), 
				FVector(BoxLoc.X + XCellLoc, BoxLoc.Y + YCellLoc, BoxLoc.Z));
		}
	}

	return;
}

void ABaseCombatGrid::FindPath(CellIndex StartCell, CellIndex FindCell, TArray<CellIndex> Path)
{
}

// Called when the game starts or when spawned
void ABaseCombatGrid::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseCombatGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsPrint)
	{
		for (auto Cell : CellsMap)
		{
			DrawDebugBox(GetWorld(), FVector(Cell.Value.X, Cell.Value.Y, Cell.Value.Z),
				FVector(DefaultCellSize, DefaultCellSize, GridBox->GetUnscaledBoxExtent().Z), ColorCell, false, DeltaTime * 2
			);
			
		}
		
	}
}

