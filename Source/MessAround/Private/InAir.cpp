// Fill out your copyright notice in the Description page of Project Settings.


#include "InAir.h"
#include "PlayerStateMachine.h"

bool UInAir::ShouldPass(UObject* obj)
{	//Cast
	APlayerStateMachine* pawn = (APlayerStateMachine*)obj;
	//If the cast was successful and we are on the ground, pass
	if (pawn != nullptr && pawn->onGround == false)
	{	//
		return true;
	}
	return false;
}

