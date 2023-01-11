// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeAffected.generated.h"

UCLASS()
class CMP302_COURSEWORK_API ATimeAffected : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimeAffected();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SetStaticMesh(UStaticMeshComponent* mesh);
	UStaticMeshComponent* GetStaticMesh();
private:
	UStaticMeshComponent* mStaticMesh;
	UMaterial* mDefaultMaterial;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnTimeEffect();

	UFUNCTION(BlueprintCallable)
		void HighlightObject();
	UFUNCTION(BlueprintCallable)
		void UnHighlightObject();

	UPROPERTY(EditAnywhere)
		UMaterial* mHighlightMaterial;
};
