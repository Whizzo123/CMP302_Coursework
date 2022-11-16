// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeSpeedCube.generated.h"

UCLASS()
class CMP302_COURSEWORK_API ATimeSpeedCube : public AActor
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
	float mDistance;
	FVector mLastPosition;
	UPROPERTY(EditAnywhere)
		float mMaxDistance;
	UPROPERTY(EditAnywhere)
		bool mSpeedUp;
	bool mUnderTimeEffect;
	UStaticMeshComponent* mStaticMesh;
	UFUNCTION(BlueprintCallable)
		void TimeEffect();
	void PrintToScreen(FString text);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
