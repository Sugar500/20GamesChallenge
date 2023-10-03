// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
ABirdCharacter::ABirdCharacter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	// In this program this is unneeded
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Set Main Input Mapping
	// Input mapping for enhanced input is found in the enhanced local player subsystem.
	// Not setting input mapping would make it not work at all
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(!PlayerController) return;
	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if(!LocalPlayer) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if(!Subsystem) return;

	// Main Input Mapping is Primary (only in this game) Input
	Subsystem->AddMappingContext(MainInputMapping, 0);
}

// Called to bind functionality to input
void ABirdCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// The enhanced input component allows one to bind Input Actions to Events and functions
	UEnhancedInputComponent* Component = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if(!Component) return;

	// Binding the function for jumping/launching on the jump action triggered
	// This allows for the player to speed up as they continue to hold a bound key
	Component->BindAction(IA_JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Launch);
}

void ABirdCharacter::Launch(const FInputActionValue& Value)
{
	// Adding a force vector in the z-axis allows the character to be launch upwards
	// Because the z-axis is up in 3D and I didn't feel like putting the extra effort into changing it
	LaunchCharacter(FVector(0.f, 0.f, LaunchSpeed), false, false);
}

// Called every frame
void ABirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
