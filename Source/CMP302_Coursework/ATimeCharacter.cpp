// Fill out your copyright notice in the Description page of Project Settings.


#include "ATimeCharacter.h"

// Sets default values
ATimeCharacter::ATimeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	mTimeRadius = CreateDefaultSubobject<USphereComponent>(TEXT("My Time Radius"));
	mTimeRadius->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	mTimeRadius->SetSphereRadius(470.0f);
	mTimeRadius->SetGenerateOverlapEvents(true);
	mTimeRadius->SetHiddenInGame(false);
	mTimeRadius->SetVisibility(true);
	mTimeRadius->SetSimulatePhysics(true);
	mTimeRadius->SetEnableGravity(false);
	mTimeRadius->ShapeColor = FColor::Red;
	mTimeRadius->OnComponentBeginOverlap.AddDynamic(this, &ATimeCharacter::OnTimeRadiusBeginOverlap);
}

// Called when the game starts or when spawned
void ATimeCharacter::BeginPlay()
{
	Super::BeginPlay();
	//mTimeRadius->SetSphereRadius(470.0f);
}

// Called every frame
void ATimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mTimeRadius->SetWorldLocation(this->GetActorLocation());
	//FString text = FString::SanitizeFloat(_mCurrentTimeJuice);
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

void ATimeCharacter::OnTimeRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mTimeObjectsInRange.Add(static_cast<ATimeAffected*>(OtherActor));
}

void ATimeCharacter::OnTimeRadiusExitOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mTimeObjectsInRange.Remove(static_cast<ATimeAffected*>(OtherActor));
}

void ATimeCharacter::PrintToScreen(FString text)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, *text);
}
