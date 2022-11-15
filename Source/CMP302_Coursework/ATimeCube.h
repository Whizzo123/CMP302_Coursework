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
	UPROPERTY(EditAnywhere)
		TArray<FVector> mRecordedPositions;
	int32 mRewindIndex;
	UPROPERTY(EditAnywhere)
		int32 mStepsToRewind;
	UStaticMeshComponent* mStaticMesh;
	bool mRewinding;
	bool mMoving;
	FVector mLastPosition;
	UPROPERTY(EditAnywhere)
		float mVelocityThreshold;
	UPROPERTY(EditAnywhere)
		float mRewindSpeed;

protected:
	void Delay(float duration, float deltaTime);
	void PrintToScreen(FString message);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Rewind();
};
