// Fill out your copyright notice in the Description page of Project Settings.


#include "DoJump.h"
#include "PlayerStateMachine.h"

bool UDoJump::ShouldPass(UObject* obj)
{
	APlayerStateMachine* pawn = (APlayerStateMachine*)obj;
	//Check for a jump input
	if (pawn != nullptr && pawn->onGround && pawn->doJump)
	{	//Set upwards velocity
		pawn->moveVector.Z = jumpVelocity;
		pawn->doJump = false;
		//We are jumping so we are not on the ground
		pawn->onGround = false;
		//Did jump
		return true;
	}
	//Did not jump
	return false;
}