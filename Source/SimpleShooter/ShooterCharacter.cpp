// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"

#include "Gun.h"

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

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,
	                       TEXT("WeaponSocket"));
	Gun->SetOwner(this);
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
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AShooterCharacter::OnSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AShooterCharacter::OnStopSprint);
	PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Pressed, this, &AShooterCharacter::Shoot);
	//PlayerInputComponent->BindAction(TEXT("Shoot"), IE_Released, this, &AShooterCharacter::OnStopShoot);
}

void AShooterCharacter::OnWalk()
{
	bIsWalking = true;
}

void AShooterCharacter::OnStopWalk()
{
	bIsWalking = false;
}

void AShooterCharacter::OnSprint()
{
	bIsSprinting = true;
}

void AShooterCharacter::OnStopSprint()
{
	bIsSprinting = false;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	//UE_LOG(LogTemp, Warning, TEXT("AxisValue = %f"), AxisValue);
	if (AxisValue == 0) { bIsJogging = false; }
	else if (bIsWalking)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * WalkSpeed);
	}
	else if (bIsSprinting)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * SprintSpeed);
	}
	else if (bIsMovingRight)
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * (JogSpeed / 1.4));
		bIsJogging = true;
	}
	else
	{
		AddMovementInput(GetActorForwardVector() * AxisValue * JogSpeed);
		bIsJogging = true;
	}
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	if (AxisValue == 0) { bIsMovingRight = false; }
	else if (bIsWalking)
	{
		AddMovementInput(GetActorRightVector() * AxisValue * WalkSpeed);
	}
	else if (bIsSprinting)
	{
		AddMovementInput(GetActorRightVector() * AxisValue * SprintSpeed);
	}
	else if (bIsJogging)
	{
		AddMovementInput(GetActorRightVector() * AxisValue * (JogSpeed / 1.4));
		bIsMovingRight = true;
	}
	else
	{
		AddMovementInput(GetActorRightVector() * AxisValue * JogSpeed);
		bIsMovingRight = true;
	}
}

void AShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}
