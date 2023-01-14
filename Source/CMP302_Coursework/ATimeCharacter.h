// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "ATimeCube.h"
#include "TimeSpeedCube.h"
#include <Components/SphereComponent.h>
#include "Components/ProgressBar.h"
#include "Camera/CameraComponent.h"
#include "ATimeCharacter.generated.h"



UCLASS()
class CMP302_COURSEWORK_API ATimeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATimeCharacter();
	UPROPERTY(EditAnywhere)
		float mDefaultStartingTimeJuice;
protected:
	UFUNCTION(BlueprintCallable)
		void RewindTime();
	UPROPERTY(EditAnywhere)
		float maxTimeJuice;
	UPROPERTY(EditAnywhere)
		UCapsuleComponent* mCapsule;
	UPROPERTY(BlueprintReadWrite)
		UProgressBar* progressBar;
	UPROPERTY(BlueprintReadWrite)
		bool mHoldingTimeButton;
	UPROPERTY(EditAnywhere)
		float mTimeReach;
	UPROPERTY(BlueprintReadWrite)
		UCameraComponent* mThirdPersonCam;
	UPROPERTY(BlueprintReadWrite)
		UCameraComponent* mFirstPersonCam;
	float _mCurrentTimeJuice;
	ATimeAffected* _mCurrentTargetedTimeObject;
	UCameraComponent* _mFollowCamera;
	UCapsuleComponent* _mCapsule;
	UInputComponent* _mInputComp;
	FVector _mSpawnPos;
	bool _mInThirdPersonMode;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void PrintToScreen(FString text);
	void TimeLineTrace();
	void DisableTimeObjectHighlight();
	UFUNCTION(BlueprintCallable)
		void SwitchToFirstPerson();
	UFUNCTION(BlueprintCallable)
		void SwitchToThirdPerson();
	UFUNCTION()
		void SetHoldingTimeButton();
	UFUNCTION()
		void SetReleaseTimeButton();
	UFUNCTION()
		void OnHitPlayer(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION(BlueprintCallable)
		void CancelRewind();
	UFUNCTION()
		void SwitchCameras();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
		void AddTimeJuice(float amountToAdd);
};
