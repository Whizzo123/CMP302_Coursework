// Fill out your copyright notice in the Description page of Project Settings.


#include "EventPressurePad.h"

// Sets default values
AEventPressurePad::AEventPressurePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEventPressurePad::BeginPlay()
{
	Super::BeginPlay();
	_mBoxCollider = FindComponentByClass<UBoxComponent>();
	_mBoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEventPressurePad::OnBoxColliderBeginOverlap);
	_mBoxCollider->OnComponentEndOverlap.AddDynamic(this, &AEventPressurePad::OnBoxColliderEndOverlap);
}

// Called every frame
void AEventPressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEventPressurePad::OnBoxColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATimeCube* hitObject = Cast<ATimeCube>(OtherActor);
	if (hitObject != nullptr)
	{
		if(mEventObject != nullptr)
			mEventObject->SetTriggered(true);
	}
}

void AEventPressurePad::OnBoxColliderEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATimeCube* hitObject = Cast<ATimeCube>(OtherActor);
	if (hitObject != nullptr)
	{
		if (mEventObject != nullptr)
			mEventObject->SetTriggered(false);
	}
}

