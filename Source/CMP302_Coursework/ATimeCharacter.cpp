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
	
}

// Called every frame
void ATimeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

// Called to bind functionality to input
void ATimeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	
}

void ATimeCharacter::RewindTime()
{
	GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Green, TEXT("Hello this is the rewind time!!"));
	TArray<AActor*> timeCubes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimeCube::StaticClass(), timeCubes);
	for (AActor* a : timeCubes)
	{
		GEngine->AddOnScreenDebugMessage(0, 15.0f, FColor::Green, TEXT("Rewinding for cube: "));
		ATimeCube* timeCube = Cast<ATimeCube>(a);
		timeCube->Rewind();
	}
	TArray<AActor*> timeSpeedCubes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATimeSpeedCube::StaticClass(), timeSpeedCubes);
	for (AActor* a : timeSpeedCubes)
	{
		ATimeSpeedCube* timeSpeedCube = Cast<ATimeSpeedCube>(a);
		timeSpeedCube->TimeEffect();
	}
}

