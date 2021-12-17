// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transition.h"
#include "OnGround.generated.h"

/**
 * 
 */
UCLASS()
class UOnGround : public UTransition
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Checks if the user is on the ground
	/// </summary>
	bool ShouldPass(UObject* obj) override;
};
