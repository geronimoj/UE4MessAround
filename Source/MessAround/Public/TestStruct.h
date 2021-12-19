// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestStruct.generated.h"

/**
 * 
 */
USTRUCT() struct MESSAROUND_API FTestStruct
{
	GENERATED_BODY();
public:
	UPROPERTY(EditAnywhere)
	float value;
};
