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
	mTimeEffectImage->SetVisibility(ESlateVisibility::Hidden);
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
			timeJuiceBar->SetPercent(_mCurrentTimeJuice / maxTimeJuice);
			_mCurrentTargetedTimeObject->OnTimeEffect();
		}
	}
}

void ATimeCharacter::AddTimeJuice(float amountToAdd)
{
	_mCurrentTimeJuice += amountToAdd;
	timeJuiceBar->SetPercent(_mCurrentTimeJuice / maxTimeJuice);
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
			SetTimeEffectImageUI();
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
	mTimeEffectImage->SetVisibility(ESlateVisibility::Hidden);
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

void ATimeCharacter::SetTimeEffectImageUI()
{
	//Sample current time effect on time object
	//Change image to that time effect image from stored images
	TimeStages state = _mCurrentTargetedTimeObject->GetCurrentTimeState();
	switch (state)
	{
	case SLOW:
		mTimeEffectImage->SetBrushFromTexture(slowTimeEffectImage);
		break;
	case STOP:
		mTimeEffectImage->SetBrushFromTexture(stopTimeEffectImage);
		break;
	case REVERSE:
		mTimeEffectImage->SetBrushFromTexture(reverseTimeEffectImage);
		break;
	case NORMAL:
		mTimeEffectImage->SetBrushFromTexture(normalTimeEffectImage);
	}
	mTimeEffectImage->SetVisibility(ESlateVisibility::Visible);
}