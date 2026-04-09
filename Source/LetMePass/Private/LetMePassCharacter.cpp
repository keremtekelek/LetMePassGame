#include "LetMePass/Public/LetMePassCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ActorComponents/AC_InteractionSystem.h"
#include "Subsystems/Subsystem_Dialogue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);



ALetMePassCharacter::ALetMePassCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Camera Settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Movement Settings
	GetCharacterMovement()->bOrientRotationToMovement = true; 	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); 
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Setup Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(GetMesh()); 
	FollowCamera->bUsePawnControlRotation = true; 
	
	// Setup Interaction System Actor Component
	AC_InteractionSystem = CreateDefaultSubobject<UAC_InteractionSystem>(TEXT("Interaction System"));

	this->Tags.Add("MainCharacter");
	
}

void ALetMePassCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Getting Dialogue Subsystem
	USubsystem_Dialogue* GameInstancePtr = GetGameInstance()->GetSubsystem<USubsystem_Dialogue>();

	if (GameInstancePtr != nullptr)
	{
		DialogueSubsystem = GameInstancePtr;
	}
}

void ALetMePassCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	
	FollowCamera->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("head"));
	FollowCamera->SetRelativeLocation(FVector(0, 12, 0));
}



void ALetMePassCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALetMePassCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALetMePassCharacter::Look);
		
		// Sprinting
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ALetMePassCharacter::SprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ALetMePassCharacter::SprintEnd);

		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ALetMePassCharacter::Interact);
		
		// Skip Dialogue
		EnhancedInputComponent->BindAction(SkipDialogueAction, ETriggerEvent::Started,this,&ALetMePassCharacter::SkipDialogue);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ALetMePassCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}



void ALetMePassCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALetMePassCharacter::SprintStart(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 420.f;
	IsCharacterSprinting = true;
}

void ALetMePassCharacter::SprintEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
	IsCharacterSprinting = false;
}

void ALetMePassCharacter::Interact(const FInputActionValue& Value)
{
	if (AC_InteractionSystem)
	{
		AC_InteractionSystem->MC_Interact();
		UE_LOG(LogTemp, Warning, TEXT("AC_InteractionSystem is valid on the player character!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AC_InteractionSystem is not valid on the player character!"))
	}
}

void ALetMePassCharacter::SkipDialogue(const FInputActionValue& Value)
{
	if (DialogueSubsystem)
	{
		DialogueSubsystem->SkipDialogue();
		UE_LOG(LogTemp, Warning, TEXT("DialogueSubsystem is valid on the player character!"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DialogueSubsystem is not valid on the player character!"))
	}
}
