// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "TeleportBarrier.generated.h"

/**
 * 
 */
UCLASS()
class MESSAROUND_API ATeleportBarrier : public ATriggerBox
{
	GENERATED_BODY()
private:
	/// <summary>
	/// The place the object will be teleported to upon touch
	/// </summary>
	AActor* respawnPoint;
public:
    /// <summary>
    /// For toggling the barrier on and off
    /// </summary>
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
        bool isActive;
	ATeleportBarrier();

    UFUNCTION()
        void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
    /// <summary>
    /// For setting the destination of the teleport
    /// </summary>
    /// <param name="destination">The destination location</param>
    UFUNCTION(BlueprintCallable)
    void SetDestination(AActor* destination);
};
