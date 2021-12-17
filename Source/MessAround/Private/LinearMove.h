// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State.h"
#include "LinearMove.generated.h"

/**
 * 
 */
UCLASS()
class ULinearMove : public UState
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	float speed = 5;

	UPROPERTY(EditAnywhere)
	float fallSpeed = 1;

	void Tick(float deltaTime, UObject* obj) override;
};
