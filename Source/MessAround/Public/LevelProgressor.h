// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStage.h"
#include "ProgressorInclude.h"
#include "LevelProgressor.generated.h"
/*
 * To Do: Store all LevelStages and don't delete them until destructor is called.
 * Swap to new progression system
 */
UCLASS()
class MESSAROUND_API ALevelProgressor : public AActor
{
	GENERATED_BODY()
private:
	/// <summary>
	/// Pointer to the current stage
	/// </summary>
	UPROPERTY(EditAnywhere)
	ULevelStage* theCurrentStage;
	/// <summary>
	/// The initial stage
	/// </summary>
	ULevelStage* initial;

	bool initialized;
public:
	// Sets default values for this actor's properties
	ALevelProgressor();
	~ALevelProgressor();

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
	/// <summary>
	/// Uses a recursive search to find the stage with the given name
	/// </summary>
	/// <param name="stageName">The name of the stage to find</param>
	/// <returns>Returns a pointer to the given stage</returns>
	UFUNCTION(BlueprintCallable)
	ULevelStage* FindStage(FString stageName);
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/// <summary>
	/// Returns the number of steps in the stage given by the name
	/// </summary>
	/// <param name="stageName">The name of the stage to get the steps for</param>
	/// <returns>Returns -1 if the stage could not be found</returns>
	UFUNCTION(BlueprintCallable)
	int GetStageSteps(FString stageName);
	/// <summary>
	/// Sets the current stage of the level progressor
	/// </summary>
	/// <param name="newStage">The stage to swap to</param>
	/// <returns>Returns false if the newStage is nullptr</returns>
	UFUNCTION(BlueprintCallable)
	bool SetCurrentStage(ULevelStage* newStage);

	UFUNCTION(BlueprintCallable)
	ULevelStage* GetCurrentStage();
	/// <summary>
	/// Initializes the first stage to be something
	/// </summary>
	UFUNCTION(BlueprintCallable)
	ULevelStage* InitializeFirstStage(FString stageName, int stepCount);
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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void GenerateStages();
	//Subscribe
	UFUNCTION(BlueprintCallable)
		void SubscribeToStage(FString stageName, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStageTick(FString stageName, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStep(FString stageName, FStepStageChange stepFunc);
	//Unsubscribe stuff
	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStage(FString stageName, EStageType stage, FStageEnterExit func);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStageTick(FString stageName, FStageTick tickFunc);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStep(FString stageName, FStepStageChange stepFunc);
};