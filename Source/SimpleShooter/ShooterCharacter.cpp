// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	// takes direct axis input, can be directly called
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);
	// referencing ACharacter.h directly, using built in jump function
	PlayerInputComponent->BindAction(TEXT("Walk"), IE_Pressed, this, &AShooterCharacter::OnWalk);
	PlayerInputComponent->BindAction(TEXT("Walk"), IE_Released, this, &AShooterCharacter::OnStopWalk);
}

void AShooterCharacter::OnWalk()
{
	bIsWalking = true;
}

void AShooterCharacter::OnStopWalk()
{
	bIsWalking = false;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	if (bIsWalking)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * WalkSpeed);
	}
	else
	{
		AddMovementInput(GetActorForwardVector() * AxisValue);
	}
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	if (bIsWalking)
	{
		AddMovementInput(GetActorRightVector() * AxisValue * WalkSpeed);
	}
	else
	{
		AddMovementInput(GetActorRightVector() * AxisValue);
	}
}
