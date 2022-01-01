// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelProgressor.h"

// Sets default values
ALevelProgressor::ALevelProgressor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Instance the current stage
	theCurrentStage = nullptr;
	initial = nullptr;
	initialized = false;
}

ALevelProgressor::~ALevelProgressor()
{	//To my understanding, UE4 manages UObjects and I shouldn't do anything.
	initial = nullptr;
	theCurrentStage = nullptr;
}

// Called when the game starts or when spawned
void ALevelProgressor::BeginPlay()
{
	Super::BeginPlay();
	//Initialize the stages
	//Not to self, don't use the for (auto variable : TArray) for structs, it does not pass by reference
}

void ALevelProgressor::SwapStage()
{	//Null catch
	if (theCurrentStage == nullptr)
		return;
	//Exit the current stage
	theCurrentStage->Exit();
	//Move to the next stage
	theCurrentStage = theCurrentStage->GetNextStage();
	//If there is a next stage, enter it
	if (theCurrentStage != nullptr)
		theCurrentStage->Enter();
	//Otherwise there are no more stages
}

bool ALevelProgressor::CheckStageCompletion()
{	//Null catch
	if (theCurrentStage == nullptr)
		return true;
	//Get the step count
	int size = theCurrentStage->GetStepCount();
	//Loop over steps and check if any have not finsihed
	for (int i = 0; i < size; i++)
		if (!theCurrentStage->GetCompletedStep(i))
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
	//Null catch
	if (theCurrentStage == nullptr || !initialized)
		return;
	//Check if the stage has been completed
	if (CheckStageCompletion())
	{	//If its done, move to the next stage
		SwapStage();
		//If theCurrentStage is null, end the level
		if (theCurrentStage == nullptr)
		{	//Call the end code
			LevelEnd();
			return;
		}
	}
	//Do the stages tick
	theCurrentStage->Tick(DeltaTime);

}

int ALevelProgressor::GetStageSteps(FString stageName)
{	//Attemp to find the given stage
	ULevelStage* temp = FindStage(stageName);
	//Make sure index is valid
	if (temp == nullptr)
		UE_LOG(LogTemp, Warning, TEXT("Could not find stage with name %s"), *stageName)
		return -1;
	//Return the count
	return temp->GetStepCount();
}

bool ALevelProgressor::SetCurrentStage(ULevelStage* newStage)
{	//Null catch
	if (newStage == nullptr)
		UE_LOG(LogTemp, Error, TEXT("Attempted to enter nullpr stage"))
		return false;
	//If the current stage is the new stage, don't enter it because we are already in it.
	if (theCurrentStage == newStage)
	{	//Log a warning but let it go through. Its not like it breaks anything.
		UE_LOG(LogTemp, Warning, TEXT("Attempted to enter the current stage"))
	}
	//Exit the current stage if not null
	if (theCurrentStage != nullptr)
		theCurrentStage->Exit();

	theCurrentStage = newStage;
	//Enter the new stage
	newStage->Enter();

	return true;
}

ULevelStage* ALevelProgressor::GetCurrentStage()
{	//Get the current stage
	return theCurrentStage;
}

ULevelStage* ALevelProgressor::InitializeFirstStage(FString stageName, int stepCount)
{	//Don't initialize something new
	if (theCurrentStage != nullptr)
		return nullptr;
	//Initialize the stage
	theCurrentStage = NewObject<ULevelStage>();
	theCurrentStage->SetName(stageName);
	theCurrentStage->SetStepCount(stepCount);

	initial = theCurrentStage;
	//Return the value
	return theCurrentStage;
}

void ALevelProgressor::SetCurrentStageStep(int stepIndex, bool completed)
{	//Index catch
	if (theCurrentStage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current stage is invalid"));
		return;
	}

	theCurrentStage->SetCompletedStep(stepIndex, completed);
}

void ALevelProgressor::Initialize()
{
	initialized = true;

	if (theCurrentStage != nullptr)
		//Initialize the stages
		theCurrentStage->Initialize();
	//Level has started
	LevelStart();
	//If the current stage is nullptr, create one
	if (theCurrentStage == nullptr)
	{	//Make sure current stage is initialized
		theCurrentStage = NewObject<ULevelStage>();
		initial = theCurrentStage;
	}
	//Enter the first stage
	if (theCurrentStage != nullptr)
		theCurrentStage->Enter();
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The initial stage has not been initialized"))
	}
}

void ALevelProgressor::LevelStart_Implementation() {}
void ALevelProgressor::LevelEnd_Implementation() {}
void ALevelProgressor::GenerateStages_Implementation() {}

void ALevelProgressor::SubscribeToStage(FString stageName, EStageType stage, FStageEnterExit func)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->SubscribeToStage(stage, func);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}

void ALevelProgressor::SubscribeToStageTick(FString stageName, FStageTick tickFunc)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->SubscribeToTick(tickFunc);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}

void ALevelProgressor::SubscribeToStep(FString stageName, FStepStageChange stepFunc)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->SubscribeToStepChange(stepFunc);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}

void ALevelProgressor::UnsubscribeToStage(FString stageName, EStageType stage, FStageEnterExit func)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->UnsubscribeToStage(stage, func);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}

void ALevelProgressor::UnsubscribeToStageTick(FString stageName, FStageTick tickFunc)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->UnsubscribeToTick(tickFunc);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}

void ALevelProgressor::UnsubscribeToStep(FString stageName, FStepStageChange stepFunc)
{
	ULevelStage* temp = FindStage(stageName);

	if (temp != nullptr)
		temp->UnsubscribeToStepChange(stepFunc);
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find stage with name %s"), *stageName)
	}
}
