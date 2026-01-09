// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/GridMovementComponent.h"

#include "AIController.h"
#include "Engine/WorldComposition.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

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

		//OwnAICont->ReceiveMoveCompleted.AddDynamic(this, &UGridMovementComponent::MoveToPointCompleted);

		FScriptDelegate Delegate;
		Delegate.BindUFunction(this, TEXT("MoveToPointCompleted"));

		OwnAICont->ReceiveMoveCompleted.AddUnique(Delegate);

		EMovePlayType = MovePlayType::Play;

		PathCounter = 0;
		//GridPath = PointsArray;
		GridPathIndex = IndexPathArray;

		OwnerGrid->GetCell(GridPathIndex[0]);

		StartMoveToPath.Broadcast(OwnChar, GridPathIndex[0],
			GridPathIndex[GridPathIndex.Num() - 1]);
		StartMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
			GridPathIndex[0]);

		OwnAICont->MoveToLocation(OwnerGrid->GetCell(GridPathIndex[PathCounter]).location, -1,
			false, false);

		return true;
	}
	else
		return false;
	

	//AICont->MoveToLocation(FVector::Zero());

}

void UGridMovementComponent::MoveToPointCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	//MyGridPointIndex = GridPathIndex[PathCounter];

	//PathCounter++;

	CompleteMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
		GridPathIndex[PathCounter]);

	if (PathCounter+1 >= GridPathIndex.Num() || EMovePlayType == MovePlayType::Stop)
	{
		CompleteMoveToPath.Broadcast(OwnChar, MyGridPointIndex,
			GridPathIndex[PathCounter]);

		MyGridPointIndex = GridPathIndex[PathCounter];

		PathCounter = 0;

		GridPathIndex.Empty();

		OwnAICont->ReceiveMoveCompleted.RemoveDynamic(this,
			&UGridMovementComponent::MoveToPointCompleted);
	}
	else
	{
		switch (EMovePlayType)
		{
			case MovePlayType::Play:
			{
				MyGridPointIndex = GridPathIndex[PathCounter];

				PathCounter++;

				StartMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
					GridPathIndex[PathCounter]);

				OwnAICont->MoveToLocation(OwnerGrid->GetCell(GridPathIndex[PathCounter]).location, 
					-1, false, false);

				break;
			}
			case MovePlayType::Pause:
			{
				OwnAICont->ReceiveMoveCompleted.RemoveDynamic(this,
					&UGridMovementComponent::MoveToPointCompleted);

				break;
			}
			///case MovePlayType::Stop:
			//{
			//	OwnAICont->ReceiveMoveCompleted.RemoveDynamic(this,
			//		&UGridMovementComponent::MoveToPointCompleted);
			//
			//	break;
			//}
		}
	}
}

void UGridMovementComponent::PauseGridMove()
{
	EMovePlayType = MovePlayType::Pause;
}

void UGridMovementComponent::PlayGridMove()
{
	EMovePlayType = MovePlayType::Play;

	if(Cast<UCharacterMovementComponent>(
		OwnChar->GetMovementComponent())->Velocity.IsNearlyZero() && PathCounter < GridPathIndex.Num())
	{
		FScriptDelegate Delegate;
		Delegate.BindUFunction(this, TEXT("MoveToPointCompleted"));

		OwnAICont->ReceiveMoveCompleted.AddUnique(Delegate);

		StartMoveToPoint.Broadcast(OwnChar, MyGridPointIndex,
			GridPathIndex[0]);

		OwnAICont->MoveToLocation(OwnerGrid->GetCell(GridPathIndex[PathCounter]).location, -1,
			false, false);
	}

	//OwnAICont->ReceiveMoveCompleted.AddDynamic(this,&UGridMovementComponent::MoveToPointCompleted);

	//Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UGridMovementComponent, MoveToPointCompleted));
}

void UGridMovementComponent::CancelGridMove()
{
	EMovePlayType = MovePlayType::Stop;
}
