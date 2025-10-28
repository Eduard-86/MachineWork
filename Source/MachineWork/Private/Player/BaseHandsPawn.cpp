// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseHandsPawn.h"

#include "VectorTypes.h"
#include "GameFramework/Character.h"


// Sets default values
ABaseHandsPawn::ABaseHandsPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeftHandPoint = CreateDefaultSubobject<USceneComponent>("LeftHandPoint");
	LeftHandPoint->SetRelativeLocation(GetActorForwardVector() * 100);
	LeftHandPoint->SetupAttachment(RootComponent);
	

	RightHandPoint = CreateDefaultSubobject<USceneComponent>("RightHandPoint");
	LeftHandPoint->SetRelativeLocation(GetActorForwardVector() * 100);
	RightHandPoint->SetupAttachment(RootComponent);

	//RightHandLoc = GetActorForwardVector() * 100 + GetActorRightVector() * 50;
	//LeftHandLoc = GetActorForwardVector() * 100 + GetActorRightVector() * -50;
}

// Called when the game starts or when spawned
void ABaseHandsPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

float ABaseHandsPawn::SetLeftHeandsLocation(FVector LeftMove)
{
	FVector ActorForward = GetActorForwardVector();
	
	FVector OldRelLeftHand = LeftHandPoint->GetRelativeLocation();


	LeftHandPoint->AddRelativeLocation(LeftMove);;

	FVector LeftRel = LeftHandPoint->GetComponentLocation() - GetActorLocation();

	if (LeftRel.Length() <= HandsLength) {
		LeftRel.Normalize();
		if (
			FVector::DotProduct(ActorForward, LeftRel) > 0.4 ||
			FVector::DotProduct(ActorForward, LeftRel) < -0.4
			)
		{
			return FVector::DotProduct(ActorForward, LeftRel);
		}
	}

	LeftHandPoint->SetRelativeLocation(OldRelLeftHand);
	return FVector::DotProduct(ActorForward, LeftRel);
}

bool ABaseHandsPawn::SetRightHeandsLocation(FVector RightMove)
{
	FVector ActorForward = GetActorForwardVector();

	FVector OldRelRightHand = RightHandPoint->GetRelativeLocation();

	RightHandPoint->AddRelativeLocation(RightMove);


	FVector RigtRel = RightHandPoint->GetComponentLocation() - GetActorLocation();

	if (RigtRel.Length() <= HandsLength) {
		RigtRel.Normalize();
		if (
			FVector::DotProduct(ActorForward, RigtRel) > 0.4 ||
			FVector::DotProduct(ActorForward, RigtRel) < -0.4
			)
		{
			return true;
		}
	}

	RightHandPoint->SetRelativeLocation(OldRelRightHand);
	return false;
}

// Called every frame
void ABaseHandsPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseHandsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

