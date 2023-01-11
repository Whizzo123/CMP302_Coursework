// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCharacter.h"

// Sets default values
ATimeCharacter::ATimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ATimeCharacter::BeginPlay()
{
	Super::BeginPlay();
	_mFollowCamera = this->FindComponentByClass<UCameraComponent>();
}

// Called every frame
void ATimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mHoldingTimeButton)
		TimeLineTrace();
	else
		DisableTimeObjectHighlight();
}

// Called to bind functionality to input
void ATimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATimeCharacter::RewindTime()
{
	if (_mCurrentTimeJuice >= 2.0f)
	{
		if (_mCurrentTargetedTimeObject != nullptr)
		{
			_mCurrentTimeJuice -= 2.0f;
			progressBar->SetPercent(_mCurrentTimeJuice / maxTimeJuice);
			_mCurrentTargetedTimeObject->OnTimeEffect();
		}
	}
}

void ATimeCharacter::AddTimeJuice(float amountToAdd)
{
	_mCurrentTimeJuice += amountToAdd;
	progressBar->SetPercent(_mCurrentTimeJuice / maxTimeJuice);
}

void ATimeCharacter::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}

void ATimeCharacter::TimeLineTrace()
{
	FVector startVec = _mFollowCamera->GetComponentLocation();
	FVector endVec = UKismetMathLibrary::GetForwardVector(_mFollowCamera->GetComponentRotation());
	endVec *= 1000.0f;
	endVec += startVec;

	FHitResult* outHit = new FHitResult();
	this->GetWorld()->LineTraceSingleByChannel(*outHit, startVec, endVec, ECollisionChannel::ECC_Visibility);
	if (outHit != nullptr && outHit->GetActor() != nullptr)
	{
		ATimeAffected* timeObject = static_cast<ATimeAffected*>(outHit->GetActor());
		if (timeObject != nullptr)
		{
			if(timeObject != _mCurrentTargetedTimeObject)
				DisableTimeObjectHighlight();
			timeObject->HighlightObject();
			_mCurrentTargetedTimeObject = timeObject;
		}
		else
			DisableTimeObjectHighlight();
	}
	else
		DisableTimeObjectHighlight();
}

void ATimeCharacter::DisableTimeObjectHighlight()
{
	if (_mCurrentTargetedTimeObject != nullptr)
	{
		_mCurrentTargetedTimeObject->UnHighlightObject();
		_mCurrentTargetedTimeObject = nullptr;
	}
}
