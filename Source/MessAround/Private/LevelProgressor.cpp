// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelProgressor.h"

// Sets default values
ALevelProgressor::ALevelProgressor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentStage = -1;
	theCurrentStage = nullptr;
	initial = nullptr;
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

ULevelStage* ALevelProgressor::FindStage(FString stageName)
{	//If the level progressor has not been setup, return nullptr
	if (initial == nullptr)
		return nullptr;
	//If initial is what is being searched for, use initial
	if (initial->GetName() == stageName)
		return initial;
	//The level stage we are starting the search from
	TArray<ULevelStage*>* closed = new TArray<ULevelStage*>();
	TArray<ULevelStage*>* open = new TArray<ULevelStage*>();
	//Initialize temporary storage data
	TArray<ULevelStage*>* toCheck = nullptr;
	ULevelStage* cur = nullptr;
	//Prepare the search
	open->Add(initial);
	//While the open list contains data, search
	//We will either eventually run out of stuff to search through
	//Or we will find our target
	while (open->Num() > 0)
	{	//Get the first item
		cur = (*open)[0];
		//Take it out of open and into closed
		open->RemoveAt(0);
		closed->Add(cur);

		toCheck = cur->GetNextStages();
		//Check through toCheck for the stage
		for (ULevelStage* stage : *toCheck)
		{	//Check the name
			if (stage->GetName() == stageName)
			{	//Clear references to make sure data is not deleted somehow.
				closed->Empty();
				open->Empty();
				//Release the memory we created
				delete closed;
				delete open;
				//Return the stage
				return stage;
			}
			//Make sure that stage has not already been checked or is already in open
			//Just in case of some very fancy progress setup
			else if (!closed->Contains(stage) && !open->Contains(stage))
				//If its not in open or closed, add it to open as it needs to be checked
				open->Add(stage);
		}
	}
	//Clear references to make sure data is not deleted somehow.
	closed->Empty();
	open->Empty();
	//Release the memory we created
	delete closed;
	delete open;
	//We could not find the target
	return nullptr;
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

ULevelStage* ALevelProgressor::GetCurrentStage()
{	//If the current stage is nullptr, create one
	if (theCurrentStage == nullptr)
	{
		theCurrentStage = NewObject<ULevelStage>();
		initial = theCurrentStage;
	}
	//Get the current stage
	return theCurrentStage;
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
	//If the current stage is nullptr, create one
	if (theCurrentStage == nullptr)
	{
		theCurrentStage = NewObject<ULevelStage>();
		initial = theCurrentStage;
	}
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
