// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"


// Sets default values
ACannon::ACannon()
{

	PrimaryActorTick.bCanEverTick = false;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!bCanFire)
	{
		return;
	}

	bCanFire = false;

	AmmoRack--;

	CannonType = ECannonType::FireProjectile;
	if (AmmoRack < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Haven't projectiles")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire Projectile")));
	}
	
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);

}

void ACannon::AutoFire()
{
	if (!bCanFire)
	{
		return;
	}


	bCanFire = false;

	AmmoRack--;

	CannonType = ECannonType::FireProjectile;
	if (AmmoRack < 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("Haven't projectiles")));
		GetWorld()->GetTimerManager().SetTimer(RateFireTimer, this, &ACannon::Reload, RateAutoFire, true, ReCharge);
	}
	else
	{
		while (AutoAmmo >= 0)
		{
			AutoAmmo--;
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire Projectile")));
		}

	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);

}

void ACannon::Reload()
{
	bCanFire = true;
}

void ACannon::FireSpecial()
{
	if (!bCanFire)
	{
		return;
	}


	bCanFire = false;
	
	Capacitor -=  0.7f;
	CannonType = ECannonType::FireTrace;
	if (Capacitor < 0.2)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Capacitor Empty")));
	}
	else
	{
	
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, FString::Printf(TEXT("Fire Trace")));

	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);

	
}



