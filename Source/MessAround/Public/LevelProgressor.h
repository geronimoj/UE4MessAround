// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelStage.h"
#include "LevelProgressorEnum.h"
#include "LevelProgressor.generated.h"

DECLARE_DYNAMIC_DELEGATE(FStageEnterExit);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStageTick, float, DeltaTime);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStepStateChange, bool, StepCompletedState);

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

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void LevelStart();

	UFUNCTION(BlueprintNativeEvent)
		void LevelEnd();

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

	UFUNCTION(BlueprintNativeEvent)
		void OnDoThing(int randomInt);
};