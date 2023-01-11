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
			OnTimeEffectOver();
		}
		_mTimeLeftUnderEffect -= DeltaTime;
	}
}

void ATimeAffected::OnTimeEffect()
{
	switch (_mCurrentState)
	{
	case SLOW:
		OnTimeEffectSlowed();
		_mCurrentlyUnderTimeEffect = true;
		_mTimeLeftUnderEffect = _mTimePerEffect;
		_mCurrentState = STOP;
		PrintToScreen("SLOWING");
		break;
	case STOP:
		OnTimeEffectStopped();
		_mTimeLeftUnderEffect = _mTimePerEffect;
		_mCurrentState = REVERSE;
		PrintToScreen("STOP");
		break;
	case REVERSE:
		OnTimeEffectReversed();
		_mTimeLeftUnderEffect = _mTimePerEffect;
		PrintToScreen("REVERSE");
		break;
	}
}

void ATimeAffected::OnTimeEffectSlowed() {}

void ATimeAffected::OnTimeEffectStopped() {}

void ATimeAffected::OnTimeEffectReversed() {}

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

void ATimeAffected::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}