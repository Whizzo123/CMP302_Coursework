// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeAffected.h"
#include "ATimeCube.generated.h"


UCLASS()
class CMP302_COURSEWORK_API ATimeCube : public ATimeAffected
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		TArray<FVector> mRecordedPositions;
	int32 mRewindIndex;
	bool mRewinding;
	UPROPERTY(EditAnywhere)
		float mRewindSpeed;
	UPROPERTY(EditAnywhere)
		float mThresholdRecordDistance;
	virtual void OnTimeEffectSlowed() override;
	virtual void OnTimeEffectStopped() override;
	virtual void OnTimeEffectReversed() override;
	virtual void OnTimeReverseCancelled() override;
	virtual void OnTimeEffectOver() override;
	
protected:
	void Delay(float duration, float deltaTime);

	FVector _mLastRecordedPosition;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ClearRewind();
};
