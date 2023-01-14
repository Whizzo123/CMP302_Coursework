// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeAffected.h"
#include "TimeSwingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class CMP302_COURSEWORK_API ATimeSwingPlatform : public ATimeAffected
{
	GENERATED_BODY()
	
public:
	ATimeSwingPlatform();

	virtual void OnTimeEffectSlowed() override;
	virtual void OnTimeEffectStopped() override;
	virtual void OnTimeEffectReversed() override;
	virtual void OnTimeEffectOver() override;
	void PrintToScreen(FString text);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		float rotPitch;
	UPROPERTY(EditAnywhere)
		float rotYaw;
	UPROPERTY(EditAnywhere)
		float rotRoll;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;
	float _mDefaultRotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
