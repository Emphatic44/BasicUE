// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBox.h"
#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Cannon.h"

// Sets default values
AProjectileBox::AProjectileBox()
{
    USceneComponent* ProjectileBoxSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = ProjectileBoxSceneComponent;

    ProjectileBoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileBoxMesh"));
    ProjectileBoxMesh->SetupAttachment(ProjectileBoxSceneComponent);

    ProjectileBoxMesh->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBox::OnMeshOverlapBegin);
    ProjectileBoxMesh->SetCollisionProfileName(FName("OverlapAll"));
    ProjectileBoxMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    ProjectileBoxMesh->SetGenerateOverlapEvents(true);
}

void AProjectileBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);

    if (TankPawn)
    {
        TankPawn->PlusProjectiles(Projectiles);
    }

	Destroy();
};


