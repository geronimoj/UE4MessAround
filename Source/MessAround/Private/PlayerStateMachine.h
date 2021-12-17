// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerStateMachine.generated.h"

UCLASS()
class APlayerStateMachine : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerStateMachine();

	UPROPERTY(EditAnywhere)
	FVector moveInput;

	/// <summary>
	/// Stores the players moveVector in world space
	/// </summary>
	UPROPERTY(BlueprintReadWrite)
	FVector moveVector;
	/// <summary>
	/// Is the character on the ground
	/// </summary>
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool onGround = true;

	bool doJump = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void GetForward(float value);
	void GetRight(float value);
	void Jump();
};