// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStage.h"

ULevelStage::ULevelStage()
{	//Default to 1 step
	steps = 1;
	completedSteps = nullptr;
}

ULevelStage::ULevelStage(FString name, int stepCount)
{
	stageName = name;
	steps = stepCount;
	completedSteps = nullptr;
}

ULevelStage::~ULevelStage()
{	//If the array was initialized, clean it up
	if (completedSteps != nullptr)
		delete[] completedSteps;
	//Reset to nullptr just in case destructor somehow gets called again
	completedSteps = nullptr;
	//Clear the spawned array
	//Apparently, UE4 does garbage collection for UObjects itself and I don't need to worry about it
	/*for (ULevelStage* stage : nextStages)
		//Nullptr catch
		if (stage != nullptr)
		{	//Delete it
			//delete stage;
			stage->ConditionalBeginDestroy();
			//Reset the nullptr to avoid magic errors in the future
			stage = nullptr;
		}*/
	//Empty the array
	nextStages.Empty();
}

void ULevelStage::SetParams(FString name, int stepCount)
{
	stageName = name;
	steps = stepCount;
	completedSteps = nullptr;
}

bool ULevelStage::GetCompletedStep(int step)
{	//Make sure index is valid and array exists
	if (completedSteps == nullptr || step < 0 || step >= steps)
		return false;
	//Return value
	return completedSteps[step];
}

void ULevelStage::SetCompletedStep(int step, bool completed)
{	//Make sure index is valid and array exists
	if (completedSteps == nullptr || step < 0 || step >= steps)
		return;
	//Set state
	completedSteps[step] = completed;
	//Execute the event
	int size = onStepChange.Num();
	for (int i = 0; i < size; i++)
		onStepChange[i].Execute(completed, step);
}

void ULevelStage::SetStepCount(int stepCount)
{	//If the values are the same, do nothing
	if (steps == stepCount)
		return;
	//Set the new value
	steps = stepCount;
	//If its been initialized, create a new array & copy over the data
	if (completedSteps != nullptr)
	{	//Create the new array
		bool* newSteps = new bool[steps];
		//Copy as much data over as we can
		//Delete the old array
		delete[] completedSteps;
		//Store the new array
		completedSteps = newSteps;
	}
}

void ULevelStage::Initialize()
{	//Create the array
	completedSteps = new bool[steps];
	//Make sure all values are false
	for (int i = 0; i < steps; i++)
		completedSteps[i] = false;
	//Tell the next stages to initialize themself
	for (ULevelStage* stage : nextStages)
		stage->Initialize();
}

void ULevelStage::Enter()
{
	int size = enter.Num();
	UE_LOG(LogTemp, Warning, TEXT("Stage Enter: Enter functions to execute %d"), size);
	//Execute the event
	for (int i = 0; i < size; i++)
		enter[i].Execute();
}

void ULevelStage::Tick(float deltaTime)
{	//Execute the event
	int size = tick.Num();
	for (int i = 0; i < size; i++)
		tick[i].Execute(deltaTime);
}

void ULevelStage::Exit()
{	//Execute the event
	int size = exit.Num();
	for (int i = 0; i < size; i++)
		exit[i].Execute();
}

ULevelStage* ULevelStage::GetNextStage()
{	//if there are 0 next stages, return nullptr
	if (nextStages.Num() < 1)
		return nullptr;
	//Get the stage index
	int stage = GetNextStageIndex();
	//Index catch
	if (stage < 0 || stage >= nextStages.Num())
		return nullptr;
	//Return the new stage
	return nextStages[stage];
}

ULevelStage* ULevelStage::AddNextStage(FString newStageName, int newStageSteps)
{	//Instance the new stage
	ULevelStage* stage = NewObject<ULevelStage>();
	stage->SetParams(newStageName, newStageSteps);
	//Store the new stage
	nextStages.Add(stage);
	//Return the new stage
	return stage;
}

void ULevelStage::AddExistingNextStage(ULevelStage* stage)
{	//Make sure pointer is valid
	if (stage == nullptr)
		return;
	//Store pointer
	nextStages.Add(stage);
	//Return the added stage
	return;
}

void ULevelStage::SubscribeToNextStageCheck(FNextStage func)
{	//If it is not bound, bind it
	if (!getNextStage.IsBound())
		getNextStage = func;
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to subscribe to NextStageCheck but NextStageCheck already has an option assigned"));
	}
}

int ULevelStage::GetNextStageIndex()
{	//Make sure is bound
	if (getNextStage.IsBound())
		//Return value
		return getNextStage.Execute(nextStages.Num());
	else if (nextStages.Num() > 1)
	{
		UE_LOG(LogTemp, Warning, TEXT("Stage has multiple next stages but no FNextStage function has been assigned"))
	}
	//Otherwise default to 0
	return 0;
}

void ULevelStage::SubscribeToStage(EStageType stage, FStageEnterExit func)
{	//Make sure the function is still bound
	if (!func.IsBound())
		return;

	//Store as an enter or exit
	switch (stage)
	{
	case EStageType::START:
		enter.Add(func);
		break;
		//Otherwise store in exit
	default:
		exit.Add(func);
		break;
	}
}

void ULevelStage::UnsubscribeToStage(EStageType stage, FStageEnterExit func)
{
	//Attempt to remove
	int removed;
	switch (stage)
	{
	case EStageType::START:
		removed = enter.Remove(func);
		break;
	default:
		removed = exit.Remove(func);
		break;
	}
	//Log an error if nothing was removed
	if (removed <= 0)
	{	//Used curly brackets because idk if this will cause errors in builds
		UE_LOG(LogTemp, Error, TEXT("Failed to Unsubscribe from stage"));
	}
}

void ULevelStage::SubscribeToTick(FStageTick func)
{	//Make sure the function is still bound
	if (!func.IsBound())
		return;
	//Store the function
	tick.Add(func);
}

void ULevelStage::UnsubscribeToTick(FStageTick func)
{	//Remove the function
	int removed = tick.Remove(func);

	if (removed <= 0)
	{	//Used curly brackets because idk if this will cause errors in builds
		UE_LOG(LogTemp, Error, TEXT("Failed to Unsubscribe from stage"));
	}
}

void ULevelStage::SubscribeToStepChange(FStepStageChange func)
{	//Make sure the function is still bound
	if (!func.IsBound())
		return;

	onStepChange.Add(func);
}

void ULevelStage::UnsubscribeToStepChange(FStepStageChange func)
{
	int removed = onStepChange.Remove(func);

	if (removed <= 0)
	{	//Used curly brackets because idk if this will cause errors in builds
		UE_LOG(LogTemp, Error, TEXT("Failed to Unsubscribe from stage"));
	}
}
