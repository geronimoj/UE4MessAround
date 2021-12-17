// Fill out your copyright notice in the Description page of Project Settings.


#include "LinearMove.h"
#include "PlayerStateMachine.h"

void ULinearMove::Tick(float deltaTime, UObject* obj)
{
	APlayerStateMachine* pawn = (APlayerStateMachine*)obj;
	//Null catch
	if (pawn == nullptr)
		return;
	//Reset horizontal movement
	pawn->moveVector.X = 0;
	pawn->moveVector.Y = 0;
	//Only take horizontal component of vector
	////////////Update to use projections
	FVector dir = FVector::VectorPlaneProject(pawn->GetActorForwardVector(), FVector::UpVector);
	dir.Normalize();

	//Apply change to moveVector including deltatime, input & speed
	pawn->moveVector += dir * (speed * pawn->moveInput.X);

	//Repeat for right
	dir = FVector::VectorPlaneProject(pawn->GetActorRightVector(), FVector::UpVector);
	dir.Normalize();

	pawn->moveVector += dir * (speed * pawn->moveInput.Y);
	//If we are not on the ground, fall
	if (!pawn->onGround)
		pawn->moveVector.Z -= fallSpeed * deltaTime;
	//If we are on the ground and falling, stop
	else if (pawn->moveVector.Z < 0)
		pawn->moveVector.Z = 0;
}