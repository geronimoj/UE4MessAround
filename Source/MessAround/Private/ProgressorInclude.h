// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ProgressorInclude.generated.h"


UENUM(BlueprintType)
enum EStageType {
	START = 0 UMETA(DisplayName = "START"),
	END = 1  UMETA(DisplayName = "END")
};


DECLARE_DYNAMIC_DELEGATE(FStageEnterExit);
DECLARE_DYNAMIC_DELEGATE_OneParam(FStageTick, float, DeltaTime);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FStepStateChange, bool, StepCompletedState, int32, Step);