// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "State.generated.h"

class UTransition;
/**
 * 
 */
UCLASS(Abstract)
class MESSAROUND_API UState : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	TArray<class UTransition*> transitions;
	/// <summary>
	/// Called when entering the state
	/// </summary>
	/// <param name="obj"></param>
	UFUNCTION(BlueprintCallable)
	virtual void Enter(UObject* obj);
	/// <summary>
	/// Called every frame
	/// </summary>
	/// <param name="deltaTime">The time that has passed</param>
	/// <param name="obj"></param>
	UFUNCTION(BlueprintCallable)
	virtual void Tick(float deltaTime, UObject* obj);
	/// <summary>
	/// Called when exiting the state
	/// </summary>
	/// <param name="obj">The object being run the state machine on</param>
	UFUNCTION(BlueprintCallable)
	virtual void Exit(UObject* obj);
};
