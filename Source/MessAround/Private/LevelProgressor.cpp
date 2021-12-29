// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelProgressor.h"

// Sets default values
ALevelProgressor::ALevelProgressor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentStage = -1;
}

// Called when the game starts or when spawned
void ALevelProgressor::BeginPlay()
{
	Super::BeginPlay();
	//Initialize the stages
	//Not to self, don't use the for (auto variable : TArray) for structs, it does not pass by reference
	int size = stages.Num();
	for (int i = 0; i < size; i++)
		stages[i]->Initialize();

	currentStage = -1;
}

void ALevelProgressor::SwapStage()
{	//Make sure index is valid
	if (currentStage < 0 || currentStage >= stages.Num())
		return;
	//Exit the current stage
	stages[currentStage]->Exit();
	//Move to the next stage
	currentStage++;
	//If there is a next stage, enter it
	if (currentStage < stages.Num())
		stages[currentStage]->Enter();
	else//If there is no more stages, set current stage to -1 so we don't have to keep checking stages.Num
		currentStage = -1;
}

bool ALevelProgressor::CheckStageCompletion()
{	//Make sure index is valid
	if (currentStage < 0 || currentStage >= stages.Num())
		return true;
	//Store temporary to reduce getting it
	ULevelStage* current = stages[currentStage];
	int size = current->GetStepCount();
	//Loop over steps and check if any have not finsihed
	for (int i = 0; i < size; i++)
		if (!current->GetCompletedStep(i))
			//If not finished, return false
			return false;

	UE_LOG(LogTemp, Warning, TEXT("Stage completed!"));
	//Otherwise all steps have passed
	return true;
}

// Called every frame
void ALevelProgressor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Make sure index is valid
	if (currentStage < 0 || currentStage >= stages.Num())
		return;
	//Check if the stage has been completed
	if (CheckStageCompletion())
	{	//If its done, move to the next stage
		SwapStage();
		//If the index has been invalidated, finish the level
		if (currentStage < 0)
		{	//Call the end code
			LevelEnd();
			return;
		}
	}
	//Do the stages tick
	stages[currentStage]->Tick(DeltaTime);

}
int ALevelProgressor::GetStageIndex(FString stageName)
{
	int size = stages.Num();
	for (int i = 0; i < size; i++)
		//Compare name
		if (stages[i]->GetName() == stageName)
			return i;
	return -1;
}
FString ALevelProgressor::GetStageName(int index)
{	//Make sure index is valid
	if (index < 0 || index >= stages.Num())
		return FString();
	//Return stage name
	return stages[index]->GetName();
}
int ALevelProgressor::GetStageStepsVName(FString stageName)
{
	int index = GetStageIndex(stageName);
	//Make sure index is valid
	if (index < 0)
		return -1;
	//Return the count
	return stages[index]->GetStepCount();
}
int ALevelProgressor::GetStageSteps(int stageIndex)
{	//Make sure index is valid
	if (stageIndex < 0 || stageIndex >= stages.Num())
		return -1;
	//Return count
	return stages[stageIndex]->GetStepCount();
}

void ALevelProgressor::SetCurrentStageStep(int stepIndex, bool completed)
{	//Index catch
	if (currentStage < 0 || currentStage >= stages.Num())
	{
		UE_LOG(LogTemp, Warning, TEXT("Current stage is invalid"));
		return;
	}

	stages[currentStage]->SetCompletedStep(stepIndex, completed);
}

void ALevelProgressor::Initialize()
{	//
	currentStage = 0;
	//Level has started
	LevelStart();
	//Enter the first stage
	if (currentStage < stages.Num())
		stages[currentStage]->Enter();
}

void ALevelProgressor::LevelStart_Implementation() {}
void ALevelProgressor::LevelEnd_Implementation() {}

void ALevelProgressor::SubscribeToStageVIndex(int index, EStageType stage, FStageEnterExit func)
{	//Invalid index catch
	if (index < 0 || index >= stages.Num())
		return;
	//Sub to stage
	stages[index]->SubscribeToStage(stage, func);
}

void ALevelProgressor::SubscribeToStageVName(FString stageName, EStageType stage, FStageEnterExit func)
{
	int index = GetStageIndex(stageName);

	SubscribeToStageVIndex(index, stage, func);
}

void ALevelProgressor::SubscribeToStageTickVIndex(int index, FStageTick tickFunc)
{	//Invalid index catch
	if (index < 0 || index >= stages.Num())
		return;
	//Sub to stage
	stages[index]->SubscribeToTick(tickFunc);
}

void ALevelProgressor::SubscribeToStageTickVName(FString stageName, FStageTick tickFunc)
{
	int index = GetStageIndex(stageName);

	SubscribeToStageTickVIndex(index, tickFunc);
}

void ALevelProgressor::SubscribeToStepVIndex(int stageIndex, FStepStageChange stepFunc)
{	//Invalid index catch
	if (stageIndex < 0 || stageIndex >= stages.Num())
		return;
	//Sub to stage
	stages[stageIndex]->SubscribeToStepChange(stepFunc);
}

void ALevelProgressor::SubscribeToStepVName(FString stageName, FStepStageChange stepFunc)
{
	int index = GetStageIndex(stageName);

	SubscribeToStepVIndex(index, stepFunc);
}

void ALevelProgressor::UnsubscribeToStageVIndex(int index, EStageType stage, FStageEnterExit func)
{	//Invalid index catch
	if (index < 0 || index >= stages.Num())
		return;
	//Sub to stage
	stages[index]->UnsubscribeToStage(stage, func);
}

void ALevelProgressor::UnsubscribeToStageVName(FString stageName, EStageType stage, FStageEnterExit func)
{
	int index = GetStageIndex(stageName);

	UnsubscribeToStageVIndex(index, stage, func);
}

void ALevelProgressor::UnsubscribeToStageTickVIndex(int index, FStageTick tickFunc)
{//Invalid index catch
	if (index < 0 || index >= stages.Num())
		return;
	//Sub to stage
	stages[index]->UnsubscribeToTick(tickFunc);
}

void ALevelProgressor::UnsubscribeToStageTickVName(FString stageName, FStageTick tickFunc)
{
	int index = GetStageIndex(stageName);

	UnsubscribeToStageTickVIndex(index, tickFunc);
}

void ALevelProgressor::UnsubscribeToStepVIndex(int stageIndex, FStepStageChange stepFunc)
{//Invalid index catch
	if (stageIndex < 0 || stageIndex >= stages.Num())
		return;
	//Sub to stage
	stages[stageIndex]->UnsubscribeToStepChange(stepFunc);
}

void ALevelProgressor::UnsubscribeToStepVName(FString stageName, FStepStageChange stepFunc)
{
	int index = GetStageIndex(stageName);

	UnsubscribeToStepVIndex(index, stepFunc);
}
