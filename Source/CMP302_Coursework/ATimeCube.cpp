// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCube.h"

// Sets default values
ATimeCube::ATimeCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mVelocityThreshold = 0.05f;
	mRewinding = false;
	mStepsToRewind = 20;
	mRewindSpeed = 10.0f;
	mRewindIndex = -1;
}

// Called when the game starts or when spawned
void ATimeCube::BeginPlay()
{
	Super::BeginPlay();
	mLastPosition = GetActorLocation();
	if (!mStaticMesh)
		mStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	mStaticMesh->SetSimulatePhysics(true);
}

// Called every frame
void ATimeCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mRewinding)
	{
		FString text = "rewindTick";
		if (mRewindIndex < 0)
		{
			mRewinding = false;
			mStaticMesh->SetSimulatePhysics(true);
			mRecordedPositions.Empty();
		}
		else
		{
			FVector rewindPos = mRecordedPositions[mRewindIndex];
			FVector currentLocation = mStaticMesh->GetComponentLocation();
			FVector newLocation = FMath::Lerp(currentLocation, rewindPos, mRewindSpeed * DeltaTime);
			mStaticMesh->SetWorldLocation(newLocation, false, nullptr, ETeleportType::TeleportPhysics);
			if(FVector::Dist(mStaticMesh->GetComponentLocation(), rewindPos) < 5.0f)
				mRewindIndex = mRewindIndex - 1;
		}
	}
	else
	{
		// Delay
		Delay(3.0f, DeltaTime);
		if (mStaticMesh->GetPhysicsLinearVelocity().Length() > mVelocityThreshold)
		{
			mMoving = true;
			mRecordedPositions.Add(mStaticMesh->GetComponentLocation());
		}
		else
		{
			mMoving = false;
		}
		mLastPosition = GetActorLocation();
	}
}

void ATimeCube::OnTimeEffect()
{
	// Determine how far back to rewind
	mRewindIndex = mRecordedPositions.Num() - 1;
	// Disable physics
	mStaticMesh->SetSimulatePhysics(false);
	mRewinding = true;
}

void ATimeCube::Delay(float duration, float deltaTime)
{
	float currentDuration = 0.0f;
	while (currentDuration < duration)
	{
		currentDuration += deltaTime;
	}
}

void ATimeCube::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}