// Fill out your copyright notice in the Description page of Project Settings.


#include "EventGate.h"

// Sets default values
AEventGate::AEventGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventGate::BeginPlay()
{
	Super::BeginPlay();
	_mStaticMesh = FindComponentByClass<UStaticMeshComponent>();
	_mClosePosition = _mStaticMesh->GetComponentLocation();
}

// Called every frame
void AEventGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mTriggered)
	{
		if (_mCurrentDistance < mDistanceToMove)
		{
			Move(1, DeltaTime);
			_mCurrentDistance = FVector::Dist(_mClosePosition, _mStaticMesh->GetComponentLocation());
		}
	}
	else
	{
		if (FVector::Dist(_mClosePosition, _mStaticMesh->GetComponentLocation()) > 1.0f)
		{
			Move(-1, DeltaTime);
		}
		else
		{
			_mStaticMesh->SetWorldLocation(_mClosePosition);
			_mCurrentDistance = 0.0f;
		}
	}
}

void AEventGate::Move(int direction, float dt)
{
	FVector moveVec = (((mGateOpenDirection * direction) * (mGateOpenSpeed * dt)) + _mStaticMesh->GetComponentLocation());
	_mStaticMesh->SetWorldLocation(moveVec);
}
