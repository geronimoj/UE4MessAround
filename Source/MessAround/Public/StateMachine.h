// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine.generated.h"

class UState;
class Transition;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MESSAROUND_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStateMachine();
	/// <summary>
	/// The previous state
	/// </summary>
	UPROPERTY(BlueprintReadOnly)
	UState* previous;
	/// <summary>
	/// The current state
	/// </summary>
	UPROPERTY(EditAnywhere)
	UState* current;
	/// <summary>
	/// The object the state machine is running on
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* targetObject;
	/// <summary>
	/// The transitions to always check
	/// </summary>
	UPROPERTY(EditAnywhere)
	TArray<class UTransition*> anyState;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	/// <summary>
	/// Gets the target if its currently nullptr
	/// </summary>
	/// <returns></returns>
	virtual UObject* GetTarget();
	/// <summary>
	/// Forces the state machine to swap to a target state
	/// </summary>
	/// <param name="target"></param>
	void ForceState(UState* target);
	/// <summary>
	/// Exits then reEnters the current state
	/// </summary>
	void ReEnterCurrent();
	/// <summary>
	/// Reverts to the previous state
	/// </summary>
	void RevertState();

private:
	/// <summary>
	/// Checks the given transitions for a pass. On a pass, returns the state that should be transitioned to
	/// </summary>
	/// <param name="transitions">The transitions to check</param>
	/// <param name="obj"></param>
	/// <returns></returns>
	UState* CheckTransitions(TArray<class UTransition*>* transitions, UObject* obj);
	/// <summary>
	/// Swaps to the given state
	/// </summary>
	/// <param name="target">The state to swap to</param>
	void SwapState(UState* target);
};
