// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSpeedCube.h"

// Sets default values
ATimeSpeedCube::ATimeSpeedCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeSpeedCube::BeginPlay()
{
	Super::BeginPlay();
	mStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	mLastPosition = mStaticMesh->GetComponentLocation();
	mSpeed = mDefaultSpeed;
}

// Called every frame
void ATimeSpeedCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector vel = mDirection * (mSpeed * DeltaTime);
	mStaticMesh->SetPhysicsLinearVelocity(vel);
	mDistance = FVector::Distance(mStaticMesh->GetComponentLocation(), mLastPosition);
	if (mDistance > mMaxDistance)
	{
		mDirection = mDirection * -1;
		mDistance = 0.0f;
		mLastPosition = mStaticMesh->GetComponentLocation();
	}
}

void ATimeSpeedCube::TimeEffect()
{
	if (mUnderTimeEffect)
	{
		mSpeed = mDefaultSpeed;
		mUnderTimeEffect = false;
	}
	else
	{
		if (mSpeedUp)
			mSpeed += mSpeedChange;
		else
			mSpeed -= mSpeedChange;
		mUnderTimeEffect = true;
	}
}

void ATimeSpeedCube::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}

