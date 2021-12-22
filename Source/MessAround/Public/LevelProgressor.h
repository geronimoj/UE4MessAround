// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStage.h"
#include "ProgressorInclude.h"
#include "LevelProgressor.generated.h"

UCLASS()
class MESSAROUND_API ALevelProgressor : public AActor
{
	GENERATED_BODY()
private:
	/// <summary>
	/// The stages for this level
	/// </summary>
	UPROPERTY(EditAnywhere)
		TArray<FLevelStage> stages;
	/// <summary>
	/// The current stage we are at
	/// </summary>
	int currentStage = 0;
public:
	// Sets default values for this actor's properties
	ALevelProgressor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/// <summary>
	/// Swaps to the next stage
	/// </summary>
	void SwapStage();
	/// <summary>
	/// Checks if the current stage has completed
	/// </summary>
	/// <returns>Returns true if the current stage has completed</returns>
	bool CheckStageCompletion();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/// <summary>
	/// Returns the index of a stage with the given name
	/// </summary>
	/// <param name="stageName">The name of the stage</param>
	/// <returns>Returns -1 if no stage was found with the given name</returns>
	int GetStageIndex(FString stageName);
	/// <summary>
	/// Returns the name of a stage at the given index
	/// </summary>
	/// <param name="index">The index of the stage</param>
	/// <returns>Returns an empty string if the index is invalid</returns>
	FString GetStageName(int index);
	/// <summary>
	/// Returns the number of steps in the stage given by the name
	/// </summary>
	/// <param name="stageName">The name of the stage to get the steps for</param>
	/// <returns>Returns -1 if the stage could not be found</returns>
	int GetStageStepsVName(FString stageName);
	/// <summary>
	/// Returns the number of steps in the stage at the given index
	/// </summary>
	/// <param name="stageIndex">The index of the stage to get for</param>
	/// <returns>Returns -1 if the index was invalid</returns>
	int GetStageSteps(int stageIndex);
	/// <summary>
	/// Sets the state of a step inside the current stage
	/// </summary>
	/// <param name="stepIndex">The index of the step</param>
	/// <param name="stageName">The state to set it too</param>
	UFUNCTION(BlueprintCallable)
	void SetCurrentStageStep(int stepIndex, bool completed);
	/// <summary>
	/// Starts the LevelProgressor running
	/// </summary>
	UFUNCTION(BlueprintCallable)
	void Initialize();
	/// <summary>
	/// Called before entering the first stage
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
		void LevelStart();
	/// <summary>
	/// Called upon exiting the final stage
	/// </summary>
	UFUNCTION(BlueprintNativeEvent)
		void LevelEnd();
	//Subscribe
	UFUNCTION(BlueprintCallable)
		void SubscribeToStageVIndex(int index, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStageVName(FString stageName, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStageTickVIndex(int index, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStageTickVName(FString stageName, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStepVIndex(int stageIndex, FStepStageChange stepFunc);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStepVName(FString stageName, FStepStageChange stepFunc);
	//Unsubscribe stuff
	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStageVIndex(int index, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStageVName(FString stageName, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStageTickVIndex(int index, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStageTickVName(FString stageName, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStepVIndex(int stageIndex, FStepStageChange stepFunc);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStepVName(FString stageName, FStepStageChange stepFunc);
};