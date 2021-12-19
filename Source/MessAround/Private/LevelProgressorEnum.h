// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelProgressorEnum.generated.h"

UENUM(BlueprintType)
enum EStageType {
	START = 0 UMETA(DisplayName = "START"),
	END = 1  UMETA(DisplayName = "END")
};
