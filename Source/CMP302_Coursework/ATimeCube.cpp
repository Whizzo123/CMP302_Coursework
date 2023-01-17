// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCube.h"

// Sets default values
ATimeCube::ATimeCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mRewinding = false;
	mRewindIndex = -1;
}

// Called when the game starts or when spawned
void ATimeCube::BeginPlay()
{
	Super::BeginPlay();
	SetStaticMesh(FindComponentByClass<UStaticMeshComponent>());
	GetStaticMesh()->SetSimulatePhysics(true);
	_mLastRecordedPosition = GetStaticMesh()->GetComponentLocation();
	mRecordedPositions.Add(_mLastRecordedPosition);
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
			GetStaticMesh()->SetSimulatePhysics(true);
			mRecordedPositions.Empty();
			OnTimeEffectOver();
		}
		else
		{
			FVector rewindPos = mRecordedPositions[mRewindIndex];
			FVector currentLocation = GetStaticMesh()->GetComponentLocation();
			FVector newLocation = FMath::Lerp(currentLocation, rewindPos, mRewindSpeed * DeltaTime);
			GetStaticMesh()->SetWorldLocation(newLocation);
			if (FVector::Dist(GetStaticMesh()->GetComponentLocation(), rewindPos) < 0.1f)
			{
				GetStaticMesh()->SetWorldLocation(rewindPos);
				mRewindIndex = mRewindIndex - 1;
			}
		}
	}
	else
	{
		if (FVector::Dist(GetStaticMesh()->GetComponentLocation(), _mLastRecordedPosition) > mThresholdRecordDistance)
		{
			mRecordedPositions.Add(GetStaticMesh()->GetComponentLocation());
			_mLastRecordedPosition = GetStaticMesh()->GetComponentLocation();
		}
		
	}
}

void ATimeCube::OnTimeEffectSlowed()
{
	
}
void ATimeCube::OnTimeEffectStopped()
{
	
}
void ATimeCube::OnTimeEffectReversed()
{
	// Determine how far back to rewind
	mRewindIndex = mRecordedPositions.Num() - 1;
	// Disable physics
	GetStaticMesh()->SetSimulatePhysics(false);
	mRewinding = true;
}

void ATimeCube::OnTimeReverseCancelled()
{
	mRewinding = false;
	GetStaticMesh()->SetSimulatePhysics(true);
	mRecordedPositions.Empty();
}

void ATimeCube::OnTimeEffectOver()
{
	
}

void ATimeCube::ClearRewind()
{
	mRecordedPositions.Empty();
}

void ATimeCube::Delay(float duration, float deltaTime)
{
	float currentDuration = 0.0f;
	while (currentDuration < duration)
	{
		currentDuration += deltaTime;
	}
}
