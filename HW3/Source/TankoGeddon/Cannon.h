// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameStruct.h"
#include "Cannon.generated.h"

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()
	
public:	
	ACannon();

	void Fire();
	void Reload();
	void FireSpecial();
	void AutoFire();



protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Components")
	class UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite,Category = "Components")
	class UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Components")
	ECannonType CannonType;   

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Components")
	float ReloadTime = 1.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Components")
	int AmmoRack = 10;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	float Capacitor = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float ReCharge = 2.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float AutoAmmo = 3.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float RateAutoFire = 2.0f;




	FTimerHandle ReloadTimer;
	FTimerHandle RateFireTimer;

private:
	bool bCanFire = true;
};
