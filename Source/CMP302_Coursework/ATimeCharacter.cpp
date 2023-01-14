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
	AddTimeJuice(mDefaultStartingTimeJuice);
	this->OnActorHit.AddDynamic(this, &ATimeCharacter::OnHitPlayer);
	_mSpawnPos = GetActorLocation();
	_mInThirdPersonMode = true;
}

void ATimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("TimeAction", IE_Pressed, this, &ATimeCharacter::RewindTime);
	PlayerInputComponent->BindAction("TimeTarget", IE_Pressed, this, &ATimeCharacter::SetHoldingTimeButton);
	PlayerInputComponent->BindAction("TimeTarget", IE_Released, this, &ATimeCharacter::SetReleaseTimeButton);
	PlayerInputComponent->BindAction("TimeCancel", IE_Pressed, this, &ATimeCharacter::CancelRewind);
	PlayerInputComponent->BindAction("SwitchCamera", IE_Pressed, this, &ATimeCharacter::SwitchCameras);
}

// Called every frame
void ATimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (mHoldingTimeButton)
		TimeLineTrace();
	else
		DisableTimeObjectHighlight();
	if (_mCurrentTimeJuice < 2.0f)
		AddTimeJuice(6.0f);
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
	FVector startVec;
	FVector endVec;
	if (_mInThirdPersonMode)
	{
		startVec = mThirdPersonCam->GetComponentLocation();
		endVec = UKismetMathLibrary::GetForwardVector(mThirdPersonCam->GetComponentRotation());
	}
	else
	{
		startVec = mFirstPersonCam->GetComponentLocation();
		endVec = UKismetMathLibrary::GetForwardVector(mFirstPersonCam->GetComponentRotation());
	}
	
	endVec *= mTimeReach;
	endVec += startVec;

	FHitResult* outHit = new FHitResult();
	this->GetWorld()->LineTraceSingleByChannel(*outHit, startVec, endVec, ECollisionChannel::ECC_Visibility);
	if (outHit != nullptr && outHit->GetActor() != nullptr)
	{
		ATimeAffected* timeObject = Cast<ATimeAffected>(outHit->GetActor());
		if (timeObject != nullptr)
		{
			if (timeObject != _mCurrentTargetedTimeObject)
			{
				DisableTimeObjectHighlight();
			}
			timeObject->HighlightObject();
			_mCurrentTargetedTimeObject = timeObject;
		}
		else
			DisableTimeObjectHighlight();
	}
	else
		DisableTimeObjectHighlight();
}

void ATimeCharacter::OnHitPlayer(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	ATimeSpeedCube* hitSpeedCube = Cast<ATimeSpeedCube>(OtherActor);
	if (hitSpeedCube != nullptr)
	{
		PrintToScreen("Hit");
		SetActorLocation(_mSpawnPos);
	}
}

void ATimeCharacter::CancelRewind()
{
	if (_mCurrentTargetedTimeObject != nullptr)
	{
		ATimeCube* timeCube = Cast<ATimeCube>(_mCurrentTargetedTimeObject);
		if (timeCube != nullptr)
			timeCube->ClearRewind();

	}
}

void ATimeCharacter::DisableTimeObjectHighlight()
{
	if (_mCurrentTargetedTimeObject != nullptr)
	{
		_mCurrentTargetedTimeObject->UnHighlightObject();
		_mCurrentTargetedTimeObject = nullptr;
	}
}

void ATimeCharacter::SetHoldingTimeButton()
{
	mHoldingTimeButton = true;
}

void ATimeCharacter::SetReleaseTimeButton()
{
	mHoldingTimeButton = false;
}

void ATimeCharacter::SwitchToFirstPerson()
{
	mThirdPersonCam->SetActive(false);
	mFirstPersonCam->SetActive(true);
	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	_mInThirdPersonMode = false;
}

void ATimeCharacter::SwitchToThirdPerson()
{
	mFirstPersonCam->SetActive(false);
	mThirdPersonCam->SetActive(true);
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	_mInThirdPersonMode = true;
}

void ATimeCharacter::SwitchCameras()
{
	if (_mInThirdPersonMode)
		SwitchToFirstPerson();
	else
		SwitchToThirdPerson();
}