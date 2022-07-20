// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ECannonType : uint8 {
	FireProjectile = 0 UMETA(DisplayName = "Use projectile"),
	FireTrace = 1 UMETA(DisplayName = "Use trace"),
	FireCub = 2 UMETA(DisplayName = "Use cub"),
	FireCilindr = 3 UMETA(DisplayName = "Use cilindr"),
	FireConus = 4 UMETA(DisplayName = "Use conus")
};

UCLASS()
class TANKOGEDDON_API UGameStructs : public UObject
{
	GENERATED_BODY()
	
};
