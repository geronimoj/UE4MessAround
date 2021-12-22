// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProgressorInclude.h"
#include "LevelStage.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct MESSAROUND_API FLevelStage
{
	GENERATED_BODY()
private:
	/// <summary>
	/// An array containing the steps that need to be completed
	/// </summary>
	bool* completedSteps;
	/// <summary>
	/// The name of the stage, for assigning events in the blueprint if you don't want to use indexes
	/// </summary>
	UPROPERTY(EditAnywhere)
	FString stageName;
	/// <summary>
	/// The steps for the levelStage
	/// </summary>
	UPROPERTY(EditAnywhere)
		int steps;
	
	/// <summary>
	/// Stores the functions to be called when entering the stage
	/// </summary>
	TArray<FStageEnterExit> enter;
	/// <summary>
	/// Stores the functions to be called when exiting the stage
	/// </summary>
	TArray<FStageEnterExit> exit;
	/// <summary>
	/// Stores the functions to be called while the stage is the currently active stage
	/// </summary>
	TArray<FStageTick> tick;
	/// <summary>
	/// Stores the functions to be called when a step in this stage changes.
	/// </summary>
	TArray<FStepStageChange> onStepChange;
public:

	FLevelStage();
	~FLevelStage();
	/// <summary>
	/// Gets the number of steps
	/// </summary>
	/// <returns></returns>
	int GetStepCount() { return steps; };
	/// <summary>
	/// Returns the name of this stage
	/// </summary>
	/// <returns></returns>
	FString GetName() { return stageName; };
	/// <summary>
	/// Gets the completed state of the step
	/// </summary>
	/// <param name="step">The step to get for</param>
	/// <returns></returns>
	bool GetCompletedStep(int step);
	/// <summary>
	/// Sets the completed state of the step
	/// </summary>
	/// <param name="step">The step to get for</param>
	/// <returns></returns>
	void SetCompletedStep(int step, bool completed);
	/// <summary>
	/// Initializes this stage
	/// </summary>
	void Initialize();
	/// <summary>
	/// Calls the Enter event
	/// </summary>
	void Enter();
	/// <summary>
	/// Calls the tick event
	/// </summary>
	/// <param name="deltaTime"></param>
	void Tick(float deltaTime);
	/// <summary>
	/// Calls the exit event
	/// </summary>
	void Exit();
	/// <summary>
	/// Subscribe a function to the enter or exit
	/// </summary>
	/// <param name="stage">Defines if it should subscribe to exit or enter</param>
	/// <param name="func">The function to subscribe with</param>
	void SubscribeToStage(EStageType stage, FStageEnterExit func);
	/// <summary>
	/// Unsubscribe a function from the enter or exit
	/// </summary>
	/// <param name="stage">Defines if it should unsubscribe from exit or enter</param>
	/// <param name="func">The function to unsubscribe</param>
	void UnsubscribeToStage(EStageType stage, FStageEnterExit func);
	/// <summary>
	/// Subscribe a function to the stages tick
	/// </summary>
	/// <param name="func">The function to subscribe with</param>
	void SubscribeToTick(FStageTick func);
	/// <summary>
	/// Unsubscribe a function from the stages tick
	/// </summary>
	/// <param name="func">The function to unsubscribe with</param>
	void UnsubscribeToTick(FStageTick func);
	/// <summary>
	/// Subscribe a function to the when a step changes state
	/// </summary>
	/// <param name="func">The function to subscribe with</param>
	void SubscribeToStepChange(FStepStageChange func);
	/// <summary>
	/// Unsubscribe a function from the when a step changes state
	/// </summary>
	/// <param name="func">The function to unsubscribe with</param>
	void UnsubscribeToStepChange(FStepStageChange func);
};