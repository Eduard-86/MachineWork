// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Pawn.h"
#include "Base_ObserverPawn.generated.h"

/*
	ObsetverPawn - ���� ������ 
	������ ���� ����� ������� ������ ��� ���� ��� ����� ����������� � ����
	AI �� ����� ����� ������ ����, �� ����� ������������ ���� ������� � ������ ����������� 
	� ������ ����������� ��� ������� ���������� ������� �� ����� � ��
*/

UCLASS()
class MACHINEWORK_API ABase_ObserverPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABase_ObserverPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* Capsule;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	UFUNCTION()
	void ZoomMove(float val);

	UFUNCTION()
		void MoveForward(float val);
	UFUNCTION()
		void MoveRight(float val);

};
