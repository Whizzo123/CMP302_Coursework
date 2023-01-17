// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventObject.generated.h"

UCLASS()
class CMP302_COURSEWORK_API AEventObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool mTriggered;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetTriggered(bool val);
};
