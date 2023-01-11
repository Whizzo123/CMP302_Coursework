// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeAffected.h"
#include "TimeStopObject.generated.h"

/**
 * 
 */
UCLASS()
class CMP302_COURSEWORK_API ATimeStopObject : public ATimeAffected
{
	GENERATED_BODY()
public:
	ATimeStopObject();
	virtual void OnTimeEffect() override;
	void PrintToScreen(FString text);
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		float mSpeed;
	UPROPERTY(EditAnywhere)
		FVector mDirection;
	UPROPERTY(EditAnywhere)
		bool mUnderTimeEffect;
	UPROPERTY(EditAnywhere)
		float mTravelDistance;
protected:
	virtual void BeginPlay() override;


	float mCurrentTravelDistance;
	FVector mLastTurningPointPosition;
};
