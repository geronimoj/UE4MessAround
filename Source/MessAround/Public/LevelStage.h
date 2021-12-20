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
};