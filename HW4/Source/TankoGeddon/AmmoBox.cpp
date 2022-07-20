// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoBox.h"
#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AAmmoBox::AAmmoBox()
{
    USceneComponent* AmmoSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = AmmoSceneComponent;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AmmoMesh"));
    Mesh->SetupAttachment(AmmoSceneComponent);

    Mesh->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
    Mesh->SetCollisionProfileName(FName("OverlapAll"));
    Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Mesh->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);

    if (TankPawn)
    {
        TankPawn->SetupCannon(CannonClass);
        Destroy();
    }
}

