// Fill out your copyright notice in the Description page of Project Settings.


#include "OnGround.h"
#include "PlayerStateMachine.h"

bool UOnGround::ShouldPass(UObject* obj)
{	//Cast
	APlayerStateMachine* pawn = (APlayerStateMachine*)obj;
	//If the cast was successful and we are on the ground, pass
	if (pawn != nullptr && pawn->onGround)
	{	//Don't need to be falling if on the ground
		pawn->moveVector.Z = 0;
		return true;
	}
	return false;
}