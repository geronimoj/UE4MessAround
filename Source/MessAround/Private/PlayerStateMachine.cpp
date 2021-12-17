// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachine.h"

// Sets default values
APlayerStateMachine::APlayerStateMachine()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerStateMachine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Get the final location
	FVector endPos = GetActorLocation() + (moveVector * DeltaTime);
	//Move the actor
	SetActorLocation(endPos, true);
}

// Called to bind functionality to input
void APlayerStateMachine::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis(TEXT("Forward"), this, &APlayerStateMachine::GetForward);
	InputComponent->BindAxis(TEXT("Right"), this, &APlayerStateMachine::GetRight);
}

void APlayerStateMachine::GetForward(float value)
{
	moveInput.X = FMath::Clamp<float>(value, -1, 1);
}

void APlayerStateMachine::GetRight(float value)
{
	moveInput.Y = FMath::Clamp<float>(value, -1, 1);
}

