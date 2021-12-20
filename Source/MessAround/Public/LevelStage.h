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
	
	
	TArray<FStageEnterExit> enter;
	TArray<FStageEnterExit> exit;
	TArray<FStageTick> tick;
	TArray<FStepStateChange> onStepChange;
public:

	FLevelStage();
	~FLevelStage();
	/// <summary>
	/// Gets the number of steps
	/// </summary>
	/// <returns></returns>
	int GetStepCount() { return steps; };

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

	//For subscribing to the enter and exit
	void SubscribeToStage(EStageType stage, FStageEnterExit func);
	//For unsubscribing to the enter and exit.
	void UnsubscribeToStage(EStageType stage, FStageEnterExit func);

	void SubscribeToTick(FStageTick func);
	
	void UnsubscribeToTick(FStageTick func);

	void SubscribeToStepChange(FStepStateChange func);

	void UnsubscribeToStepChange(FStepStateChange func);
};