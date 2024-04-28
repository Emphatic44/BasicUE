// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

 #include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharater.generated.h"

UCLASS()
class ALCHEMY_API AMainCharater : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharater();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void MoveForward (float Value);
	void MoveRight (float Value);

	void Jump();
	void StopJump();

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Camera")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Camera")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category="Movement")
	float TargetAxisValue = 0.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Animation")
	UAnimMontage* JumpAnimation;
	
};
