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

FVector ABaseCombatGrid::GetCellLocation(FCellIndex CellIndex)
{

	return CellsMap.Find(CellIndex)->location;
}

FCellIndex ABaseCombatGrid::GetGridSize()
{
	return FCellIndex(GridRow, GridColumn);
}

// �������� ���� ������� �� ���������� 
#define CalculateDistanceCell(a, b) FMath::Abs(int(a.row) - int(b.row)) + FMath::Abs(int(a.column) - int(b.column))
// ��� ������� ��������� ������ ��������� �� ���� ������ ���, ���������� ��� �������� ������������ � �������� �������� ���������
void ABaseCombatGrid::FindPath(FCellIndex StartCell, FCellIndex FinishCell, TArray<FCellIndex> & Path)
{
	if (StartCell.row >= GridRow || StartCell.column >= GridColumn || FinishCell.row >= GridRow || FinishCell.column >= GridColumn)
	{
		Path.Reset();
		return;
	}


	bool bDiagonalLastStep = false;

	FCellIndex CellStep = StartCell;

	Path.Reset();

	while (CellStep != FinishCell)
	{
		TArray<FCellIndex> StepsAroundArray;

		TArray<FCombatGridCell> CellAroundWeightsArray;


		for (int rowindex = -1; rowindex != 2; rowindex++)
		{
			if (int(rowindex) + CellStep.row < 0 || GridRow < (int(rowindex) + CellStep.row))
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

		//* CellsMap.Find(StepCell)->passability
		if (bDiagonalLastStep)
		{
			for (FCellIndex StepCell : StepsAroundArray)
			{
				uint8 StepPassability = CalculateDistanceCell(StepCell, FinishCell) + 1;

				int rowsu = StepCell.row - CellStep.row;

				int colsu = StepCell.column - CellStep.column;

				int sum = FMath::Abs(rowsu) - FMath::Abs(colsu);

				if (!sum)
				{
					StepPassability = StepPassability + 2;
				}

				CellAroundWeightsArray.Add(FCombatGridCell(StepCell, FVector::Zero(), StepPassability));
			}
		}
		else
		{
			for (FCellIndex StepCell : StepsAroundArray)
				CellAroundWeightsArray.Add(FCombatGridCell(StepCell, FVector::Zero(),
					CalculateDistanceCell(StepCell, FinishCell) + 1));
		}

		CellAroundWeightsArray.Sort();

		FCellIndex SortCell = CellAroundWeightsArray[0].index;

		int rowsu = SortCell.row - CellStep.row;
		int colsu = SortCell.column - CellStep.column;
		int sum = FMath::Abs(rowsu) - FMath::Abs(colsu);

		bDiagonalLastStep = !sum;

		Path.Add(SortCell);

		CellStep = SortCell;
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
			DrawDebugBox(GetWorld(), FVector(Cell.Value.location.X, Cell.Value.location.Y, Cell.Value.location.Z),
				FVector(DefaultCellSize, DefaultCellSize, GridBox->GetUnscaledBoxExtent().Z), ColorCell, false, DeltaTime * 2
			);
			
		}
		
	}
}

