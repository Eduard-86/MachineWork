// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/GridMovementComponent.h"

#include "AIController.h"
#include "Engine/WorldComposition.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UGridMovementComponent::UGridMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;
}


// Called when the game starts
void UGridMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(OwnerGrid))
		GetOwner()->SetActorLocation(OwnerGrid->GetCellLocation(StartCell));
	else
		ensure(IsValid(OwnerGrid));
}

void UGridMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();

	IsOwnerChar = IsValid(Cast<ACharacter>(GetOwner()));

	GridPathIndex.Empty();

	MyGridPointIndex = StartCell;

	//if (IsValid(OwnerGrid))
	//	MyGridPoint = OwnerGrid->GetCell(StartCell);
}

void UGridMovementComponent::PostInitProperties()
{
	Super::PostInitProperties();

	//IsOwnerChar = IsValid(Cast<ACharacter>(GetOwner()));

	//GridPath.Empty();

	//if (IsValid(OwnerGrid))
		//MyGridPoint = OwnerGrid->GetCell(StartCell);

}


// Called every frame
void UGridMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UGridMovementComponent::StartMoveToGrid(TArray<FCellIndex> IndexPathArray)
{
	if (OwnChar = Cast<ACharacter>(GetOwner()))
	{
		OwnAICont = Cast<AAIController>(OwnChar->GetController());

		OwnAICont->ReceiveMoveCompleted.AddDynamic(this, 
			&UGridMovementComponent::MoveToPointCompleted);

		PathCounter = 0;
		//GridPath = PointsArray;
		GridPathIndex = IndexPathArray;

		OwnerGrid->GetCell(GridPathIndex[0]);

		StartMoveToPath.Broadcast(OwnChar, GridPathIndex[0],
			GridPathIndex[GridPathIndex.Num() - 1]);
		StartMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
			GridPathIndex[0]);

		OwnAICont->MoveToLocation(OwnerGrid->GetCell(GridPathIndex[0]).location, -1,
			false, false);

		return true;
	}
	else
		return false;
	

	//AICont->MoveToLocation(FVector::Zero());

}

void UGridMovementComponent::MoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	MyGridPointIndex = GridPathIndex[PathCounter];

	PathCounter++;

	CompleteMoveToPoint.Broadcast(OwnChar, GridPathIndex[PathCounter - 1],
		MyGridPointIndex);

	if(PathCounter < GridPathIndex.Num())
	{
		StartMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
			GridPathIndex[0]);

		OwnAICont->MoveToLocation(OwnerGrid->GetCell(GridPathIndex[PathCounter]).location, -1,
			false, false);
	}
	else
	{
		CompleteMoveToPath.Broadcast(OwnChar, GridPathIndex[0],
			MyGridPointIndex);

		GridPathIndex.Empty();

		OwnAICont->ReceiveMoveCompleted.RemoveDynamic(this,
			&UGridMovementComponent::MoveToPointCompleted);

	}
}
