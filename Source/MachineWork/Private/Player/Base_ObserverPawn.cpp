// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Base_ObserverPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABase_ObserverPawn::ABase_ObserverPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Root"));
	RootComponent = Capsule;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 200.f; // The camera follows at this distance behind the character	
	//CameraBoom->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	//CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


}

// Called when the game starts or when spawned
void ABase_ObserverPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABase_ObserverPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABase_ObserverPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//PlayerInputComponent->BindAction("ZoomUp/Down", IE_Pressed, this, &ABase_ObserverPawn::ZoomMove);

	PlayerInputComponent->BindAxis("ZoomUp / Down", this, &ABase_ObserverPawn::ZoomMove);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &ABase_ObserverPawn::MoveForward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &ABase_ObserverPawn::MoveRight);

}

void ABase_ObserverPawn::ZoomMove(float val)
{

	if(val)
		CameraBoom->TargetArmLength = CameraBoom->TargetArmLength + val * 10;

	//key.Axis();
	this->StaticClass();
	
	/*
	float a;
	if (AController* Cont = GetLocalViewingPlayerController())
	{
		a = Cont->GetInputAxisKeyValue(key);
		a = Cont->InputComponent->GetAxisKeyValue(key);
	}*/
		

	//float b = a;
}

void ABase_ObserverPawn::MoveForward(float val)
{
	if ((Controller != nullptr) && (val != 0.0f))
	{
		SetActorLocation(
			FVector(
				GetActorLocation().X + -val * 10,
				GetActorLocation().Y,
				GetActorLocation().Z));
		
		//AddMovementInput(FVector(0.0, 1.0, 0.0), val);
	}
}

void ABase_ObserverPawn::MoveRight(float val)
{
	if ((Controller != nullptr) && (val != 0.0f))
	{
		SetActorLocation(
			FVector(
				GetActorLocation().X,
				GetActorLocation().Y + -val * 10,
				GetActorLocation().Z));
	}
}

