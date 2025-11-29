// Fill out your copyright notice in the Description page of Project Settings.


#include "FT_SprintGateManager.h"

// Define the static instance here which is needed in C++ files <- Stupid C++, and unreal build system! we should use a UGameInstanceSubsystem for this!
AFT_SprintGateManager* AFT_SprintGateManager::instance;

// Sets default values
AFT_SprintGateManager::AFT_SprintGateManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	gatesPassed = 0;
	timePassed = 0;
}

// Called when the game starts or when spawned
void AFT_SprintGateManager::BeginPlay()
{
	Super::BeginPlay();

	// check for multiple managers in level
	if(instance == nullptr)
	{
		// we are the one and only
		instance = this;
	}
	else
	{
		// we are a duplicate, destroy ourself
		UE_LOG(LogTemp, Warning, TEXT("Multiple Sprint Gate Managers detected in level!"));
		Destroy();	
	}

	// get all the sprint gates in the level
	TArray<AActor*> foundGates;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Gate", foundGates);
	for (AActor* actor : foundGates)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sprint Gate found: %s"), *actor->GetName());
	    AFT_SprintGate* gate = Cast<AFT_SprintGate>(actor);
	    if (gate)
	    {
	        sprintGates.Add(gate);
	    }
	}
	UE_LOG(LogTemp, Warning, TEXT("Total Sprint Gates found: %d"), sprintGates.Num());
}

// Called every frame
void AFT_SprintGateManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (gatesPassed > 0)
	{
		timePassed += DeltaTime;
		if(timePassed >= gateTimeLimit)
		{
			// time's up, reset the track
			ResetTrack();
		}
	}
}

// method to tell all the sprint gates the track is complete shutdown
void AFT_SprintGateManager::CompleteTrack()
{
	UE_LOG(LogTemp, Warning, TEXT("Track complete! Smashed it!"));
	gatesPassed = 0;
	timePassed = 0.0f;
	for (AFT_SprintGate* gate : sprintGates)
	{	if(gate)
		{ 
			gate->completedTrack = true;
		}
	}
}

// every time a gate is passed they will signal this function
void AFT_SprintGateManager::GatePassed()
{
	UE_LOG(LogTemp, Warning, TEXT("Gate Passed!"));
	// keep track of the gates passed
	gatesPassed++;
	// reset the clock, you could probably improve this a bit
	timePassed = 0;
	UE_LOG(LogTemp, Warning, TEXT("Total Gates Passed: %d"), gatesPassed);
	UE_LOG(LogTemp, Warning, TEXT("Total Sprint Gates found: %d"), sprintGates.Num());
	// if all gates are passed then complete the track
	if (gatesPassed >= sprintGates.Num())
	{
		CompleteTrack();
	}
	
}

// reset all the gates to false, and reset the tracking variables
void AFT_SprintGateManager::ResetTrack()
{
	UE_LOG(LogTemp, Warning, TEXT("Track failed reseting!"));
	// set all the gates to false
	for (AFT_SprintGate* gate : sprintGates)
	{
		gate->isTriggered = false;
	}
	// reset tracking variables
	gatesPassed = 0;
	timePassed = 0.0f;
}

void AFT_SprintGateManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UE_LOG(LogTemp, Warning, TEXT("Sprint Gate Manager EndPlay called."));
	if (instance == this)
	{
		instance = nullptr;
	}
}