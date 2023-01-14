// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventObject.h"
#include "EventElevator.generated.h"

UCLASS()
class CMP302_COURSEWORK_API AEventElevator : public AEventObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventElevator();
	UPROPERTY(EditAnywhere)
		float mSpeed;
	UPROPERTY(EditAnywhere)
		FVector mDirection;
	UPROPERTY(EditAnywhere)
		float mMaxDistance;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector _mLastPosition;
	float _mCurrentDistance;
	UStaticMeshComponent* _mStaticMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
