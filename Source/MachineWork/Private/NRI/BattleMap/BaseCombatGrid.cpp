// Fill out your copyright notice in the Description page of Project Settings.

#include "NRI/BattleMap/BaseCombatGrid.h"

#include "MeshPaintVisualize.h"
#include "Components/BoxComponent.h"


#if UE_BUILD_DEBUG
Fuint32 GetTypeHash(const FCellIndex& Explain) {
	uint32 Hash = FCrc::MemCrc32(&Explain, sizeof(FCellIndex));
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

// Called when the game starts or when spawned
void ABaseCombatGrid::BeginPlay()
{
	Super::BeginPlay();

	CalculateCells(DefaultCellSize, ColorCell);
}

void ABaseCombatGrid::CallInEditorDraeCellBoxes()
{
	CalculateCells(DefaultCellSize, ColorCell);

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

void ABaseCombatGrid::CalculateCells(float CellSize, FColor CellColor)
{
	FVector GridBoxScaleVector = GridBox->GetUnscaledBoxExtent();
	FVector BoxLoc = GridBox->GetComponentLocation();

	GridRow = (GridBoxScaleVector.Y) / CellSize;
	GridColumn = (GridBoxScaleVector.X) / CellSize;


	float YCellLoc;
	float FullCellSize = CellSize * 2;


	for (int i = 0; i < GridRow; i++)
	{
		float XCellLoc;
		YCellLoc = GridBoxScaleVector.Y * -1 + (CellSize + (FullCellSize * i));

		for (int j = 0; j < GridColumn; j++)
		{
			XCellLoc = GridBoxScaleVector.X * -1 + (CellSize + (FullCellSize * j));

			CellsMap.Add(FCellIndex(i, j),
			FCombatGridCell(
					FCellIndex(i, j),
					FVector(BoxLoc.X + XCellLoc, BoxLoc.Y + YCellLoc, BoxLoc.Z),
					1));
		}
	}

	return;
}

// допилить чтоб считало по диогонаоли 
#define CalculateDistanceCell(а, b) FMath::Abs((int(а.row) - int(b.row)) + (int(а.column) - int(b.column)))

// так считаем эвристику тоесть дистанцию до цели каждый шаг, складываем его индексом проходимости и получаем желаемый результат
void ABaseCombatGrid::FindPath(FCellIndex StartCell, FCellIndex FinishCell, TArray<FCellIndex> & Path)
{
	bool bDiagonal = false;

	FCellIndex CellStep = StartCell;

	TArray<FCellIndex> StepsAroundArray;

	TArray<FCombatGridCell> CellWeightsArray;


	for (int rowindex = -1 ; rowindex != 2; rowindex++)
	{
		if(int(rowindex) + CellStep.row < 0 || GridRow < (int(rowindex) + CellStep.row))
			continue;

		for (int colunmnindex = -1; colunmnindex != 2; colunmnindex++)
		{
			if (int(colunmnindex) + CellStep.column < 0 || GridColumn < (int(colunmnindex) + CellStep.column))
				continue;

			if (!colunmnindex && !rowindex)
				continue;

			StepsAroundArray.Add(FCellIndex(rowindex + CellStep.row, colunmnindex + CellStep.column));
		}
	}
	
	for (FCellIndex StepCell : StepsAroundArray)
	{
		int locrow = StepCell.row;
		int locrow1 = FinishCell.row;

		int loccol = StepCell.column;
		int loccol1 = FinishCell.column;

		int res = (locrow - locrow1) + (loccol - loccol);

		

		CellWeightsArray.Add(FCombatGridCell(StepCell, FVector::Zero(), CalculateDistanceCell(StepCell, FinishCell)));
		
	}

	int a = 1 - 4;

	CellWeightsArray.Sort();

	//CellStep != FinishCell
	while (false)
	{
		FCombatGridCell* CombatCell = CellsMap.Find(FCellIndex(CellStep.row-1, CellStep.column-1));
		if(CombatCell && CellStep == CombatCell->index)
		{
			
		}
		int prok = CalculateDistanceCell(StartCell, FinishCell);

	}
	
}


// Called every frame
void ABaseCombatGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(IsPrint)
	{
		for (auto Cell : CellsMap)
		{
			//DrawDebugBox(GetWorld(), FVector(Cell.Value.X, Cell.Value.Y, Cell.Value.Z),
			//	FVector(DefaultCellSize, DefaultCellSize, GridBox->GetUnscaledBoxExtent().Z), ColorCell, false, DeltaTime * 2
			//);
			
		}
		
	}
}

