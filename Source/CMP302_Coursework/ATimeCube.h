// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATimeCube.generated.h"

UCLASS()
class CMP302_COURSEWORK_API ATimeCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeCube();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	TArray<FVector> mRecordedPositions;
	int32 mRewindIndex;
	UPROPERTY(EditAnywhere)
		int32 mStepsToRewind;
	UStaticMeshComponent* mStaticMesh;
	bool mRewinding;
	bool mMoving;
	FVector mLastPosition;
	float mVelocityThreshold;
	float mRewindSpeed;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Rewind();
};
