// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventObject.h"
#include "EventGate.generated.h"

UCLASS()
class CMP302_COURSEWORK_API AEventGate : public AEventObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventGate();
	UPROPERTY(EditAnywhere)
		float mDistanceToMove;
	UPROPERTY(EditAnywhere)
		FVector mGateOpenDirection;
	UPROPERTY(EditAnywhere)
		float mGateOpenSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float _mCurrentDistance;
	FVector _mClosePosition;
	UStaticMeshComponent* _mStaticMesh;
	void Move(int direction, float dt);
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
