// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "ForceMove.generated.h"

/**
 * 
 */
UCLASS()
class UForceMove : public UState
{
	GENERATED_BODY()
public:
	/// <summary>
	/// Force to apply each frame
	/// </summary>
	UPROPERTY(EditAnywhere)
	float force = 100;

	UPROPERTY(EditAnywhere)
	float fallSpeed = 100;

	void Tick(float deltaTime, UObject* obj) override;
};
