// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharater.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AMainCharater::AMainCharater()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm ->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 300.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera ->SetupAttachment(SpringArm);

	SpringArm->bUsePawnControlRotation=true;
	Camera->bUsePawnControlRotation=false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw=false;
	bUseControllerRotationRoll=false;

}

void AMainCharater::SetupPlayerInputComponent(UInputComponent* MyInput)
{
	Super::SetupPlayerInputComponent(MyInput);

	MyInput->BindAxis("MoveForward",this,&AMainCharater::MoveForward);
	MyInput->BindAxis("MoveRight",this,&AMainCharater::MoveRight);
	
	MyInput->BindAxis("Turn",this,&AMainCharater::AddControllerYawInput);
	MyInput->BindAxis("LookUp",this,&AMainCharater::AddControllerPitchInput);

	MyInput->BindAction("Jump",IE_Pressed,this,&AMainCharater::Jump);
	MyInput->BindAction("Jump",IE_Released,this,&AMainCharater::StopJump);
}

void AMainCharater::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharater::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction,Value);
}

void AMainCharater::Jump()
{
	Super::Jump();

	bPressedJump=true;
	
	if(JumpAnimation&&CanJump())
	{
		
		PlayAnimMontage(JumpAnimation, 1.0, NAME_None);
		
	}
}

void AMainCharater::StopJump()
{
	bPressedJump=false;
}



