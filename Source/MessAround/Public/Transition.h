// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Transition.generated.h"

class UState;
/**
 * 
 */
UCLASS(Abstract)
class MESSAROUND_API UTransition : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	UState* targetState;
	/// <summary>
	/// Checks if you should swap to the target state
	/// </summary>
	/// <param name="obj"></param>
	/// <returns></returns>
	virtual bool ShouldPass(UObject* obj);
};
