// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Gadgets/Gadget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isSwinging = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GEngine != nullptr);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMappingContext, 0);
		}
	}

	//Spawn a default Gadget
	if(DefaultGadget)
	{
		//Setup default paramaters
		FActorSpawnParameters Params;
		Params.Owner = this;
		AGadget* SpawnedGadget = GetWorld()->SpawnActor<AGadget>(DefaultGadget,Params);

		//Set the transform to the socket and attach it
		SpawnedGadget->SetActorTransform(GetMesh()->GetSocketTransform(FName("gadget_r")),false,nullptr,ETeleportType::TeleportPhysics);
		SpawnedGadget->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepWorldTransform,FName("gadget_r"));
	}
}

void APlayerCharacter::Jump(const FInputActionValue& value)
{
	ACharacter::Jump();
}

void APlayerCharacter::Move(const FInputActionValue& value)
{
	const FVector2d movementVector = value.Get<FVector2d>();

	const FRotator rotation = GetController()->GetControlRotation();
	const FRotator yawRotation(0.f,rotation.Yaw,0.f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(forwardDirection, movementVector.Y);

	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(rightDirection, movementVector.X);
}

void APlayerCharacter::Swing(const FInputActionValue& value)
{
	isSwinging = true;
}

void APlayerCharacter::Prone(const FInputActionValue& value)
{
	isProning = value.Get<bool>();

	if(isProning)
	{
		Crouch();
	}else
	{
		UnCrouch();
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Jump);
		//Directional movement
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		//Directional Swing
		EnhancedInputComponent->BindAction(SwingAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Swing);
		//Proning / laying down
		EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Started, this, &APlayerCharacter::Prone);
		EnhancedInputComponent->BindAction(ProneAction, ETriggerEvent::Completed, this, &APlayerCharacter::Prone);

	}
	
}

bool APlayerCharacter::getIsSwinging()
{
	return isSwinging;
}

void APlayerCharacter::setIsSwinging(bool swings)
{
	isSwinging = swings;
}

void APlayerCharacter::SetIsProning(bool proning)
{
	isProning = proning;
}

bool APlayerCharacter::getIsProning()
{
	return isProning;
}

