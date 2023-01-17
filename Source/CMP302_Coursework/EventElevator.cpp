// Fill out your copyright notice in the Description page of Project Settings.


#include "EventElevator.h"

// Sets default values
AEventElevator::AEventElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventElevator::BeginPlay()
{
	Super::BeginPlay();
	_mStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	_mLastPosition = _mStaticMesh->GetComponentLocation();
}

// Called every frame
void AEventElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mTriggered)
	{
		_mStaticMesh->SetWorldLocation(_mStaticMesh->GetComponentLocation() + (mDirection * (mSpeed * DeltaTime)));
		_mCurrentDistance = FVector::Dist(_mLastPosition, _mStaticMesh->GetComponentLocation());
		if (_mCurrentDistance > mMaxDistance)
		{
			mDirection *= -1;
			_mCurrentDistance = 0.0f;
			_mLastPosition = _mStaticMesh->GetComponentLocation();
		}
	}
}

