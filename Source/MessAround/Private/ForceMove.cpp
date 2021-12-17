// Fill out your copyright notice in the Description page of Project Settings.


#include "ForceMove.h"
#include "PlayerStateMachine.h"

void UForceMove::Tick(float deltaTime, UObject* obj)
{
	APlayerStateMachine* pawn = (APlayerStateMachine*)obj;
	//Null catch
	if (pawn == nullptr)
		return;

	FVector dir = pawn->GetActorForwardVector();
	dir.Z = 0;
	dir.Normalize();
	//Apply change to moveVector including deltatime, input & speed
	pawn->moveVector += dir * (force * pawn->moveInput.X * deltaTime);

		//Repeat for right
		dir = pawn->GetActorRightVector();
	dir.Z = 0;
	dir.Normalize();

	pawn->moveVector += dir * (force * pawn->moveInput.Y * deltaTime);
	//If we are not on the ground, fall
	if (!pawn->onGround)
		pawn->moveVector.Z -= fallSpeed * deltaTime;
	//If we are on the ground and falling, stop
	else if (pawn->moveVector.Z < 0)
		pawn->moveVector.Z = 0;
}
