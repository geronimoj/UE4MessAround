// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Transition.h"
#include "DoJump.generated.h"

/**
 * 
 */
UCLASS()
class UDoJump : public UTransition
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Upwards jump velocity
	/// </summary>
	UPROPERTY(EditAnywhere)
	float jumpVelocity = 20;

	bool ShouldPass(UObject* obj) override;
};
