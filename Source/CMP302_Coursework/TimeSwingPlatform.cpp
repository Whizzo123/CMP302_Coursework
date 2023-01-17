// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeSwingPlatform.h"

// Sets default values
ATimeSwingPlatform::ATimeSwingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeSwingPlatform::BeginPlay()
{
	Super::BeginPlay();
	SetStaticMesh(FindComponentByClass<UStaticMeshComponent>());
	GetStaticMesh()->SetNotifyRigidBodyCollision(true);
	_mDefaultRotationSpeed = rotationSpeed;
}

// Called every frame
void ATimeSwingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (rotationSpeed != 0.0f)
	{
		FRotator rotation = FRotator(rotPitch * rotationSpeed, rotYaw * rotationSpeed, rotRoll * rotationSpeed);

		FQuat quatRotation = FQuat(rotation);
		AddActorLocalRotation(quatRotation, false, 0, ETeleportType::None);
	}
}

void ATimeSwingPlatform::OnTimeEffectSlowed()
{
	rotationSpeed /= 2;
}
void ATimeSwingPlatform::OnTimeEffectStopped()
{
	rotationSpeed = 0.0f;
}
void ATimeSwingPlatform::OnTimeEffectReversed()
{
	rotationSpeed += _mDefaultRotationSpeed * -1;
}
void ATimeSwingPlatform::OnTimeEffectOver()
{
	rotationSpeed = _mDefaultRotationSpeed;
}


