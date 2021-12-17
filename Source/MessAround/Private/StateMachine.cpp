// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine.h"
#include "State.h"
#include "Transition.h"

// Sets default values for this component's properties
UStateMachine::UStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachine::BeginPlay()
{
	Super::BeginPlay();

	//Get the target
	if (targetObject == nullptr)
		targetObject = GetTarget();
	//Enter the current state
	if (targetObject != nullptr && current != nullptr)
		current->Enter(targetObject);
}


// Called every frame
void UStateMachine::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//Make sure we have a target
	if (targetObject == nullptr)
	{	//Get target
		targetObject = GetTarget();
		//If still null, return
		if (targetObject == nullptr)
			return;
	}
	//Check global transitions
	UState* target = CheckTransitions(&anyState, targetObject);
	//Check the target transitions
	if (target == nullptr && current != nullptr)
		target = CheckTransitions(&current->transitions, targetObject);
	//Swap to the target state
	SwapState(target);
	//Call tick on target state
	if (current != nullptr)
		current->Tick(DeltaTime, targetObject);
}

UObject* UStateMachine::GetTarget()
{
	return GetOwner();
}

void UStateMachine::ForceState(UState* target)
{	//Swap to the target state
	SwapState(target);
}

void UStateMachine::ReEnterCurrent()
{	//Exit then enter the state
	current->Exit(targetObject);
	current->Enter(targetObject);
}

void UStateMachine::RevertState()
{	//Swap to the previous state
	SwapState(previous);
}

UState* UStateMachine::CheckTransitions(TArray<class UTransition*>* transitions, UObject* obj)
{	//Loop over the given transitions
	for (auto* trans : *transitions)
	{	//Return the first transition that passes
		if (trans->ShouldPass(obj))
			return trans->targetState;
	}
	//Otherwise return nullptr
	return nullptr;
}

void UStateMachine::SwapState(UState* target)
{	//Null catchs
	if (target == nullptr || target == current || targetObject == nullptr)
		return;
	//Exit previous
	if (current != nullptr)
		current->Exit(targetObject);
	//Enter
	target->Enter(targetObject);
	//Swap pointers
	previous = current;
	current = target;
}

