// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportBarrier.h"

ATeleportBarrier::ATeleportBarrier()
{
	respawnPoint = nullptr;
	isActive = true;
	bGenerateOverlapEventsDuringLevelStreaming = true;

	OnActorBeginOverlap.__Internal_AddDynamic(this, &ATeleportBarrier::OnOverlapBegin, TEXT("OnOverlapBegin"));
}

void ATeleportBarrier::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Checking for teleport"))
	//Make sure is active
		if (!isActive)
		{
			UE_LOG(LogTemp, Warning, TEXT("Teleporter is disabled"))
				return;
		}
	//If there is no respawn point, exit
	if (respawnPoint == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TeleportBarrier has no destination set"))
			return;
	}
	//Saftey check because I never trust pointers.
	if (OtherActor == nullptr || OverlappedActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("OtherActor is nullptr"))
			return;
	}
	//This could probably be stacked to reduce/change how memory is allocated. I think thats a thing anyways
	//OtherActor->SetActorTransform(respawnPoint->GetActorTransform());
	UE_LOG(LogTemp, Warning, TEXT("Beginning Teleport"))
		//Get the transform
		auto trans = respawnPoint->GetActorTransform();
		//Teleport to the new position
	OtherActor->SetActorTransform(trans);
		UE_LOG(LogTemp, Warning, TEXT("Target teleported"))
}

void ATeleportBarrier::SetDestination(AActor* destination)
{
	respawnPoint = destination;
}
