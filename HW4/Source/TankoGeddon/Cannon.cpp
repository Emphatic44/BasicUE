// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Projectile.h"

// Sets default values
ACannon::ACannon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

// Called when the game starts or when spawned
void ACannon::Fire()
{
	if (!ReadyToFire)
	{
		return;
	}

	ReadyToFire = false;

	if ((Type == ECannonType::FireProjectile) && (AmmoFire > 0))
	{
		AmmoFire--;

		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile. AmmoFire = %d"), AmmoFire));
	
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass,ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
		if (projectile)
		{
			projectile->Start();
		}
	}
	else
	{
		if ((Type == ECannonType::FireTrace) && (AmmoTrace > 0))
		{
			AmmoTrace--;

			GEngine->AddOnScreenDebugMessage(2, 1, FColor::Green, FString::Printf(TEXT("Fire - trace. AmmoTrace = %d"), AmmoTrace));
			
			FHitResult hitResult;
			FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
			traceParams.bTraceComplex = true;
			traceParams.bReturnPhysicalMaterial = false;

			FVector StartTrace = ProjectileSpawnPoint->GetComponentLocation();
			FVector EndTrace = ProjectileSpawnPoint->GetForwardVector() * FireRange + StartTrace;

			if (GetWorld()->LineTraceSingleByChannel(hitResult, StartTrace, EndTrace, ECollisionChannel::ECC_Visibility, traceParams))
			{
				DrawDebugLine(GetWorld(), StartTrace, hitResult.Location, FColor::Red, false, 0.2f, 0, 10);
				if (hitResult.GetActor())
				{
					hitResult.GetActor()->Destroy();
				}
			}
			else
			{
				DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red, false, 0.2f, 0, 10);
			}

		}
		else
		{
			if ((Type == ECannonType::FireCub) && (AmmoCub > 0))
			{
				AmmoCub--;

				GEngine->AddOnScreenDebugMessage(3, 1, FColor::Green, FString::Printf(TEXT("Fire - cub. AmmoCub = %d"), AmmoCub));

				AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
				if (projectile)
				{
					projectile->Start();
				}
			}
			else
			{
				if ((Type == ECannonType::FireCilindr) && (AmmoCilindr > 0))
				{
					AmmoCilindr--;

					GEngine->AddOnScreenDebugMessage(4, 1, FColor::Green, FString::Printf(TEXT("Fire - cilindr. AmmoCilindr = %d"), AmmoCilindr));

					AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
					if (projectile)
					{
						projectile->Start();
					}
				}
				else
				{
					if ((Type == ECannonType::FireConus) && (AmmoConus > 0))
					{
						AmmoConus--;

						GEngine->AddOnScreenDebugMessage(5, 1, FColor::Green, FString::Printf(TEXT("Fire - conus. AmmoConus = %d"), AmmoConus));

						AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(), ProjectileSpawnPoint->GetComponentRotation());
						if (projectile)
						{
							projectile->Start();
						}
					}
					else

					{
						GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, FString::Printf(TEXT("Not Fire. Fire = %d , Trace = %d , Cub = %d , Cilindr = %d , Conus = %d"), AmmoFire, AmmoTrace, AmmoCub, AmmoCilindr, AmmoConus));
					}
				}
			}
		}	
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

void ACannon::FireSpecial()
{
	if (!ReadyToFire)
	{
		return;
	}

	ReadyToFire = false;

	if ((Type == ECannonType::FireProjectile) && (AmmoFire > 0))
	{
		AmmoFire--;

		GEngine->AddOnScreenDebugMessage(11, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile1")));
		GEngine->AddOnScreenDebugMessage(12, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile2")));
		GEngine->AddOnScreenDebugMessage(13, 1, FColor::Green, FString::Printf(TEXT("Fire - projectile3. AmmoFire = %d"), AmmoFire));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, FString::Printf(TEXT("Not Fire. Fire = %d , Trace = %d , Cub = %d , Cilindr = %d , Conus = %d"), AmmoFire, AmmoTrace, AmmoCub, AmmoCilindr, AmmoConus));
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::PlusProjectiles(float num)
{
		if ((Type == ECannonType::FireProjectile) && (AmmoFire < 100))
		{
			AmmoFire = AmmoFire + num;
		}

		if ((Type == ECannonType::FireTrace) && (AmmoTrace < 100))
		{
			AmmoTrace = AmmoTrace + num;
		}

		if ((Type == ECannonType::FireCub) && (AmmoCub < 100))
		{
			AmmoCub = AmmoCub + num;
		}

		if ((Type == ECannonType::FireCilindr) && (AmmoCilindr < 100))
		{
			AmmoCilindr = AmmoCilindr + num;
		}

		if ((Type == ECannonType::FireConus) && (AmmoConus < 100))
		{
			AmmoConus = AmmoConus + num;
		}
}

/*void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
}*/
