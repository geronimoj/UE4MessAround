// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelStage.h"

FLevelStage::FLevelStage()
{	//Default to 1 step
	steps = 1;
	completedSteps = nullptr;
}

FLevelStage::~FLevelStage()
{	//If the array was initialized, clean it up
	if (completedSteps != nullptr)
		delete[] completedSteps;
	//Reset to nullptr just in case destructor somehow gets called again
	completedSteps = nullptr;
}

bool FLevelStage::GetCompletedStep(int step)
{	//Make sure index is valid and array exists
	if (completedSteps == nullptr || step < 0 || step >= steps)
		return false;
	//Return value
	return completedSteps[step];
}

void FLevelStage::SetCompletedStep(int step, bool completed)
{	//Make sure index is valid and array exists
	if (completedSteps == nullptr || step < 0 || step >= steps)
		return;
	//Set state
	completedSteps[step] = completed;
}

void FLevelStage::Initialize()
{	//Create the array
	completedSteps = new bool[steps];
	//Make sure all values are false
	for (int i = 0; i < steps; i++)
		completedSteps[i] = false;
}
