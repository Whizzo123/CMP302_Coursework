// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EventObject.h"
#include "ATimeCube.h"
#include "Components/BoxComponent.h"
#include "EventPressurePad.generated.h"

UCLASS()
class CMP302_COURSEWORK_API AEventPressurePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventPressurePad();
	UPROPERTY(EditAnywhere)
		AEventObject* mEventObject;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UBoxComponent* _mBoxCollider;
	UFUNCTION()
		void OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
