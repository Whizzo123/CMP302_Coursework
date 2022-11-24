// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCharacter.h"

// Sets default values
ATimeCharacter::ATimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mTimeRadius = CreateDefaultSubobject<USphereComponent>(TEXT("My Time Radius"));
	mTimeRadius->SetSphereRadius(470.0f);
	del.BindUFunction(this, FName("OnTimeRadiusBeginOverlap"));
	mTimeRadius->OnComponentBeginOverlap.Add(del);
}

// Called when the game starts or when spawned
void ATimeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FString text = FString::SanitizeFloat(_mCurrentTimeJuice);
	//PrintToScreen(text);
}

// Called to bind functionality to input
void ATimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ATimeCharacter::RewindTime()
{
	if (_mCurrentTimeJuice > 0.0f)
	{
		GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Green, TEXT("Hello this is the rewind time!!"));
		if(mTimeObjectsInRange.Num() > 0)
			_mCurrentTimeJuice -= 2.0f;
		for (ATimeAffected* timeObject : mTimeObjectsInRange)
		{
			timeObject->OnTimeEffect();
		}
		
	}
	else
		PrintToScreen("Out of Juice");
}

void ATimeCharacter::AddTimeJuice(float amountToAdd)
{
	_mCurrentTimeJuice += amountToAdd;
}

void ATimeCharacter::OnTimeRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ATimeCharacter::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}
