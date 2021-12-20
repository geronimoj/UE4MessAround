// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProgressorInclude.generated.h"


UENUM(BlueprintType)
enum EStageType {
	START = 0 UMETA(DisplayName = "START"),
	END = 1  UMETA(DisplayName = "END")
};

/// <summary>
/// IN ORDER TO DEFINE DELEGATES IN A HEADER FILES FOR INCLUSION IN OTHER FILES. MAKE SURE THERE IS A UNREAL CLASS, STRUCT or ENUM INSIDE THE FILE!
/// </summary>
DECLARE_DYNAMIC_DELEGATE(FStageEnterExit);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStageTick, float, DeltaTime);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FStepStateChange, bool, StepCompletedState, int32, Step);