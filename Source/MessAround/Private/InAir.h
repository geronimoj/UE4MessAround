// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transition.h"
#include "InAir.generated.h"

/**
 * 
 */
UCLASS()
class UInAir : public UTransition
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Checks if the user is airborne
	/// </summary>
	bool ShouldPass(UObject* obj) override;
};
