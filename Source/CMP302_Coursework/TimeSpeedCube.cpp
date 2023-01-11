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
	SetStaticMesh(FindComponentByClass<UStaticMeshComponent>());
	mLastPosition = GetStaticMesh()->GetComponentLocation();
	mSpeed = mDefaultSpeed;
}

// Called every frame
void ATimeSpeedCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector vel = mDirection * (mSpeed * DeltaTime);
	GetStaticMesh()->SetPhysicsLinearVelocity(vel);
	mDistance = FVector::Distance(GetStaticMesh()->GetComponentLocation(), mLastPosition);
	if (mDistance > mMaxDistance)
	{
		mDirection = mDirection * -1;
		mDistance = 0.0f;
		mLastPosition = GetStaticMesh()->GetComponentLocation();
	}
}

void ATimeSpeedCube::OnTimeEffectSlowed()
{
	mSpeed -= mSpeedChange;
}
void ATimeSpeedCube::OnTimeEffectStopped()
{
	mSpeed = 0;
}
void ATimeSpeedCube::OnTimeEffectReversed()
{
	mDirection *= -1;
	mSpeed = mDefaultSpeed - mSpeedChange;
}
void ATimeSpeedCube::OnTimeEffectOver()
{
	mSpeed = mDefaultSpeed;
	if (_mCurrentState == REVERSE)
	{
		mDirection *= -1;
	}
	_mCurrentState = SLOW;
}

void ATimeSpeedCube::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}

