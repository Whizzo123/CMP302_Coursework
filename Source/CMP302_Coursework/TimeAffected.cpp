// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAffected.h"

// Sets default values
ATimeAffected::ATimeAffected()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeAffected::BeginPlay()
{
	Super::BeginPlay();
	_mCurrentState = NORMAL;
}

// Called every frame
void ATimeAffected::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (_mCurrentlyUnderTimeEffect)
	{
		if (_mTimeLeftUnderEffect <= 0)
		{
			_mCurrentlyUnderTimeEffect = false;
			_mCurrentState = NORMAL;
			OnTimeEffectOver();
		}
		_mTimeLeftUnderEffect -= DeltaTime;
	}
}

void ATimeAffected::OnTimeEffect()
{
	if (_mCurrentState == REVERSE)
		_mCurrentState = NORMAL;
	_mCurrentState = (TimeStages)((int)_mCurrentState + 1);
	switch (_mCurrentState)
	{
	case SLOW:
		OnTimeEffectSlowed();
		_mCurrentlyUnderTimeEffect = true;
		_mTimeLeftUnderEffect = _mTimePerEffect;
		break;
	case STOP:
		OnTimeEffectStopped();
		_mTimeLeftUnderEffect = _mTimePerEffect;
		break;
	case REVERSE:
		OnTimeEffectReversed();
		_mTimeLeftUnderEffect = _mTimePerEffect;
		break;
	}
}

void ATimeAffected::OnTimeEffectSlowed() {}

void ATimeAffected::OnTimeEffectStopped() {}

void ATimeAffected::OnTimeEffectReversed() {}

void ATimeAffected::OnTimeReverseCancelled() {}

void ATimeAffected::OnTimeEffectOver() {}

void ATimeAffected::HighlightObject()
{
	if(mStaticMesh != nullptr)
		mStaticMesh->SetMaterial(0, mHighlightMaterial);
}

void ATimeAffected::UnHighlightObject()
{
	mStaticMesh->SetMaterial(0, mDefaultMaterial);
}

void ATimeAffected::SetStaticMesh(UStaticMeshComponent* mesh)
{
	mStaticMesh = mesh;
	mDefaultMaterial = mStaticMesh->GetMaterial(0)->GetMaterial();
}

UStaticMeshComponent* ATimeAffected::GetStaticMesh()
{
	return mStaticMesh;
}



TimeStages ATimeAffected::GetCurrentTimeState()
{
	return _mCurrentState;
}