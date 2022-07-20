// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CannonMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRate = 1;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireRange = 1000;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	float FireDamage = 1; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
	ECannonType Type = ECannonType::FireProjectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
	TSubclassOf<class AProjectile> ProjectileClass;

	FTimerHandle ReloadTimerHandle;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoFire = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoTrace = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoCub = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoCilindr = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	int32 AmmoConus = 100;

private:
	bool ReadyToFire = true;
	
public:	
	// Sets default values for this actor's properties
	ACannon();

	void Fire();

	void FireSpecial();

	bool IsReadyToFire();

	void Reload();

	void PlusProjectiles(float num);

/*protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;*/

};