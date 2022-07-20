// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"

/*DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);*/

// Sets default values
ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject< UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::MoveForward(float Value)
{
	TargetForwardAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	if (Cannon)
	{
		Cannon->FireSpecial();
	}
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Tank movement
	FVector CurrentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = CurrentLocation + (forwardVector * MoveSpeed * TargetForwardAxisValue * DeltaSeconds) + (rightVector * MoveSpeed * TargetRightAxisValue * DeltaSeconds);
	SetActorLocation(movePosition, true);

	// Tank rotation
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, RotateRightAxisValue, InterpolationKey);
	/*UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxis Value: %f, RotateRightAxisValue: %f"), CurrentRightAxisValue, RotateRightAxisValue);*/
	float YawRotation = RotationSpeed * RotateRightAxisValue * DeltaSeconds;
	FRotator CurrentRotation = GetActorRotation();
	YawRotation = CurrentRotation.Yaw + YawRotation;
	FRotator newRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(newRotation);

	// Turret rotation
	
	FVector mousePos = TankPlayerController->GetMousePos();

	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
	FRotator TurretRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = TurretRotation.Pitch;
	targetRotation.Roll = TurretRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TurretRotationInterpolationKey));
}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<ATankPlayerController>(GetController());

	SetupCannon(CannonClass);
}

void ATankPawn::SetupCannon(TSubclassOf<ACannon> newCannonClass)
{
	if (!newCannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}
	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(newCannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void ATankPawn::ChangeCannon()
{
	//Change weapon
	TSubclassOf<ACannon> cachedCannon = CannonClass;
	CannonClass = SecondCannonClass;
	SecondCannonClass = cachedCannon;

	//EquipWeapon
	SetupCannon(CannonClass);
}

void ATankPawn::PlusProjectiles(float num)
{
	if (Cannon)
	{
		Cannon->PlusProjectiles(num);
	}
}



