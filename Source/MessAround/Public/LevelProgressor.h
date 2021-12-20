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

	UPROPERTY(EditAnywhere)
		TArray<FLevelStage> stages;
public:
	// Sets default values for this actor's properties
	ALevelProgressor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void SwapStage();

	bool CheckStageCompletion();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	int GetStageIndex(FString stageName);

	FString GetStageName(int index);

	int GetStageStepsVName();

	int GetStageSteps(int stageIndex);

	UFUNCTION(BlueprintNativeEvent)
		void LevelStart();

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
		void SubscribeToStepVIndex(int stageIndex, int stepIndex, FStepStateChange stepFunc);

	UFUNCTION(BlueprintCallable)
		void SubscribeToStepVName(FString stageName, int stepIndex, FStepStateChange stepFunc);
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
		void UnsubscribeToStepVIndex(int stageIndex, int stepIndex, FStepStateChange stepFunc);

	UFUNCTION(BlueprintCallable)
		void UnsubscribeToStepVName(FString stageName, int stepIndex, FStepStateChange stepFunc);
};