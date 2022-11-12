// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCube.h"

// Sets default values
ATimeCube::ATimeCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATimeCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimeCube::Rewind()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("REWINDING HERE WE GO!!!!"));
	// Determine how far back to rewind
	mRewindIndex = mRecordedPositions.Num() - mStepsToRewind;
	// Disable physics
	if(!mStaticMesh)
		mStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	mStaticMesh->SetSimulatePhysics(false);
	mRewinding = true;
}