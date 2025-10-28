// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base_ObserverPawn.h"

#include "BaseHandsPawn.generated.h"

UCLASS()
class MACHINEWORK_API ABaseHandsPawn : public ABase_ObserverPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABaseHandsPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:

	UFUNCTION(BlueprintCallable)
	float SetLeftHeandsLocation(FVector LeftMove);

	UFUNCTION(BlueprintCallable)
	bool SetRightHeandsLocation(FVector RightMove);


	//UPROPERTY(BlueprintReadOnly)
	//FVector LeftHandLoc;
	//UPROPERTY(BlueprintReadOnly)
	//FVector RightHandLoc;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hands")
	TObjectPtr<USceneComponent> LeftHandPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Hands")
	TObjectPtr<USceneComponent> RightHandPoint;

public:

	UPROPERTY(EditAnywhere)
	float HandsLength = 300.f;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
