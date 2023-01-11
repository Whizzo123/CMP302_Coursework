// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeStopObject.h"

ATimeStopObject::ATimeStopObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATimeStopObject::BeginPlay()
{
	Super::BeginPlay();
	SetStaticMesh(FindComponentByClass<UStaticMeshComponent>());
	mLastTurningPointPosition = GetStaticMesh()->GetComponentLocation();
}

void ATimeStopObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!mUnderTimeEffect)
	{
		FVector vel = mDirection * (mSpeed * DeltaTime);
		GetStaticMesh()->SetPhysicsLinearVelocity(vel);
		mCurrentTravelDistance = FVector::Distance(GetStaticMesh()->GetComponentLocation(), mLastTurningPointPosition);
		if (mCurrentTravelDistance > mTravelDistance)
		{
			mDirection *= -1;
			mCurrentTravelDistance = 0.0f;
			mLastTurningPointPosition = GetStaticMesh()->GetComponentLocation();
		}
	}
}

void ATimeStopObject::OnTimeEffect()
{
	mUnderTimeEffect = !mUnderTimeEffect;
}