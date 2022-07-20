// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankPawn.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
	InputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPlayerController::FireSpecial); 
	InputComponent->BindAction("ChangeCannon", IE_Pressed, this, &ATankPlayerController::ChangeCannon);
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector TankPosition = TankPawn->GetActorLocation();
	MousePos.Z = TankPosition.Z;

	FVector dir = MousePos - TankPosition;
	dir.Normalize();
	MousePos = TankPosition + dir * 1000.0f;
	//DrawDebugLine(GetWorld(), TankPosition, MousePos, FColor::Green, false, 0.3f, 0, 5);
}

/*void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	TankPawn = Cast<ATankPawn>(InPawn);
}*/

void ATankPlayerController::MoveForward(float Value)
{
	if (TankPawn)
		TankPawn->MoveForward(Value);
}

void ATankPlayerController::MoveRight(float Value)
{
	if (TankPawn)
		TankPawn->MoveRight(Value);
}

void ATankPlayerController::RotateRight(float Value)
{
	if (TankPawn)
		TankPawn->RotateRight(Value);
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::FireSpecial()
{
	TankPawn->FireSpecial();
}

void ATankPlayerController::ChangeCannon()
{
	TankPawn->ChangeCannon();
}