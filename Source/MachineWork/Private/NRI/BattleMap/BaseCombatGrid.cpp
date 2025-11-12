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
	CalculateCells(DefaultCellSize, ColorCell);

	Super::BeginPlay();
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

	GridRow = ((GridBoxScaleVector.Y) / CellSize);
	GridColumn = ((GridBoxScaleVector.X) / CellSize);


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

FCellIndex ABaseCombatGrid::FindCellUsingVector(FVector FindLocation)
{
	FVector GridBoxScaleVector = GridBox->GetUnscaledBoxExtent();
	FVector BoxLoc = GridBox->GetComponentLocation();

	FVector LocalFindLocation = FindLocation - BoxLoc;

	FVector LocationByBoxScale = GridBoxScaleVector + LocalFindLocation;

	int FindCellRow = (LocationByBoxScale.Y / 2) / DefaultCellSize;

	int FindCellColumn = (LocationByBoxScale.X / 2) / DefaultCellSize;


	if (FindCellRow > GridRow - 1 || FindCellColumn > GridColumn - 1)
		return FCellIndex();
	else
		return FCellIndex(FindCellRow, FindCellColumn);
}

// допилить чтоб считало по диогонаоли 
#define CalculateDistanceCell(a, b) FMath::Abs(int(a.row) - int(b.row)) + FMath::Abs(int(a.column) - int(b.column))
// так считаем эвристику тоесть дистанцию до цели каждый шаг, складываем его индексом проходимости и получаем желаемый результат
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

		if(StepsAroundArray.IsEmpty())
		{
			checkf(true, TEXT("Do not find one cell around cell"));
			return;
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

		uint8 OnePassability = 0;

		for(int i = 1; i < CellAroundWeightsArray.Num(); i++)
		{
			if (CellAroundWeightsArray[0].passability == CellAroundWeightsArray[i].passability)
				OnePassability++;
			else
				break;
		}

		FCellIndex* SortCell;


		if (OnePassability > 0)
		{
			/* разбирись, аргоритм не работает
			 *
			 *
		 * »з каждой точки нужно вз¤ть направление
		 * StepCell - CellAroundWeightsArray = 1.1 - 1.2, 1.1 - 2.1, 1.1 - 2.2 = получем напровление 0.1, 1.0, 1.1
		 * ѕосле найдЄм с этими напровлени¤ми скал¤рное произведение между ними и расто¤нием до точки = StepCell - FinishCell = 1.1 - 3.6 = 2.5
		 * скол¤рное произведение выгл¤дит так = (0,1) Ј (2,5) = 0*2 + 1*5 = 5!, (1,0) Ј (2,5) = 1*2 + 0*5 = 2!
		 * находим большее скол¤рное произведение, это и будет лучшей клеткой!
		 */
			OnePassability++;

			FVector2D PathDistance(
				FMath::Abs(int(CellStep.row - FinishCell.row)), FMath::Abs(int(CellStep.column - FinishCell.column)));

			TArray<FVector2D> OnePassabilityCellsVector;

			for (int i = 0; i < OnePassability; i++)
			{
				OnePassabilityCellsVector.Add(
					FVector2D(
						int(CellAroundWeightsArray[i].index.row - CellStep.row),
						int(CellAroundWeightsArray[i].index.column - CellStep.column)));
			}

			TArray<int> DotArray;

			for (int i = 0; i < OnePassability; i++)
			{
				DotArray.Add(OnePassabilityCellsVector[i].X * PathDistance.X +
					OnePassabilityCellsVector[i].Y * PathDistance.Y);
			}

			uint8 BestCellIndex = 0;

			for (int i = 1; i < OnePassability; i++)
			{
				if (DotArray[BestCellIndex] < DotArray[i])
					BestCellIndex = i;
			}

			//
			SortCell = &CellAroundWeightsArray[BestCellIndex].index;
		}
		else 
			SortCell = &CellAroundWeightsArray[0].index;

		

		uint8 rowsu = FMath::Abs(SortCell->row - CellStep.row);
		uint8 colsu = FMath::Abs(SortCell->column - CellStep.column);
		uint8 sum = FMath::Abs(rowsu - colsu);

		bDiagonalLastStep = !sum;

		Path.Add(*SortCell);

		CellStep = *SortCell;
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

