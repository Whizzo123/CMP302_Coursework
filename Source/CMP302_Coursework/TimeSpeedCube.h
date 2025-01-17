// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimeAffected.h"
#include "TimeSpeedCube.generated.h"

UCLASS()
class CMP302_COURSEWORK_API ATimeSpeedCube : public ATimeAffected
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeSpeedCube();
	float mSpeed;
	UPROPERTY(EditAnywhere)
		float mDefaultSpeed;
	UPROPERTY(EditAnywhere)
		float mSpeedChange;
	UPROPERTY(EditAnywhere)
		FVector mDirection;
	virtual void OnTimeEffectSlowed() override;
	virtual void OnTimeEffectStopped() override;
	virtual void OnTimeEffectReversed() override;
	virtual void OnTimeEffectOver() override;
	
	UFUNCTION()
		void OnHitObject(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
