// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"

AMyGameMode::AMyGameMode() : Super()
{
	ConstructorHelpers::FClassFinder<APawn>MainCharater(TEXT("/Game/Main/Charachers/Main_Char/BP_MainChar"));

	DefaultPawnClass = MainCharater.Class;
}
