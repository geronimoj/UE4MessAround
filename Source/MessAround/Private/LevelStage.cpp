// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStage.h"

ULevelStage::ULevelStage()
{	//Default to 1 step
	steps = 1;
	completedSteps = nullptr;
}

ULevelStage::~ULevelStage()
{	//If the array was initialized, clean it up
	if (completedSteps != nullptr)
		delete[] completedSteps;
	//Reset to nullptr just in case destructor somehow gets called again
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

void ULevelStage::Initialize()
{	//Create the array
	completedSteps = new bool[steps];
	//Make sure all values are false
	for (int i = 0; i < steps; i++)
		completedSteps[i] = false;
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

int ULevelStage::GetNextStage()
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
