// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FT_SprintGate.h"
#include "Kismet/GameplayStatics.h"
#include "FT_SprintGateManager.generated.h"


UCLASS()
class FT_SPRINT_API AFT_SprintGateManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFT_SprintGateManager();
	// store all sprint gates in level
	TArray<AFT_SprintGate*> sprintGates;
	// basic singleton access check
	static AFT_SprintGateManager* instance;

private:
	// keep track of how many gates are passed
	int gatesPassed = 0;
	// the time inbetween each gate allowed
	int gateTimeLimit = 5;
	// the time left for the player to get to the next gate
	float timePassed = 0.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// every time a gate is passed they will signal this function
	void GatePassed();

private:
	// method to tell all the sprint gates the track is complete shutdown
	void CompleteTrack();
	// reset all the gates to false, and reset the tracking variables
	void ResetTrack();

};
