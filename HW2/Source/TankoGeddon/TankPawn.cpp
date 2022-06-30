#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ATankPawn::ATankPawn()
{

	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::MoveForward(float Value)
{
	TargetAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	TargetAxisValue = Value;
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	

	FVector CurrentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector movePosition = CurrentLocation + forwardVector * MoveSpeed * TargetAxisValue;
	SetActorLocation(movePosition, true);



	FVector rightVector =GetActorRightVector();
	FVector movePositionRotate = CurrentLocation + rightVector * MoveSpeed * TargetAxisValue;
	SetActorLocation(movePositionRotate, true);
}

