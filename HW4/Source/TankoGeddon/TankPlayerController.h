// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATankPawn;

/**
 * 
 */
UCLASS()
class TANKOGEDDON_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		ATankPawn* TankPawn;
	UPROPERTY()
		FVector MousePos;
	
public:
	ATankPlayerController();
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	FVector GetMousePos() { return MousePos; };

	/*UPROPERTY()
		class ATankPawn* TankPawn;

	virtual void SetPawn(APawn* InPawn) override;*/

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void RotateRight(float Value);

	UFUNCTION()
	void Fire();

	UFUNCTION()
	void FireSpecial();

	UFUNCTION()
	void ChangeCannon();
};
