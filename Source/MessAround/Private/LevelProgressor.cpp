// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelProgressor.h"

// Sets default values
ALevelProgressor::ALevelProgressor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelProgressor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelProgressor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ALevelProgressor::LevelStart_Implementation() {}
void ALevelProgressor::LevelEnd_Implementation() {}

void ALevelProgressor::OnDoThing_Implementation(int randomInt)
{	//Default stuff
}

void ALevelProgressor::SubscribeToStageVIndex(int index, EStageType stage, FStageEnterExit func)
{
}

void ALevelProgressor::SubscribeToStageVName(FString stageName, EStageType stage, FStageEnterExit func)
{
}

void ALevelProgressor::SubscribeToStageTickVIndex(int index, FStageTick tickFunc)
{
}

void ALevelProgressor::SubscribeToStageTickVName(FString stageName, FStageTick tickFunc)
{
}

void ALevelProgressor::SubscribeToStepVIndex(int stageIndex, int stepIndex, FStepStateChange stepFunc)
{
}

void ALevelProgressor::SubscribeToStepVName(FString stageName, int stepIndex, FStepStateChange stepFunc)
{
}
