// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeAffected.h"

// Sets default values
ATimeAffected::ATimeAffected()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimeAffected::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATimeAffected::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimeAffected::OnTimeEffect()
{

}

void ATimeAffected::HighlightObject()
{
	mStaticMesh->SetMaterial(0, mHighlightMaterial);
}

void ATimeAffected::UnHighlightObject()
{
	mStaticMesh->SetMaterial(0, mDefaultMaterial);
}

void ATimeAffected::SetStaticMesh(UStaticMeshComponent* mesh)
{
	mStaticMesh = mesh;
	mDefaultMaterial = mStaticMesh->GetMaterial(0)->GetMaterial();
}

UStaticMeshComponent* ATimeAffected::GetStaticMesh()
{
	return mStaticMesh;
}