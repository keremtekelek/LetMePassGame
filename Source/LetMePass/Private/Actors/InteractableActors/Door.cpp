#include "Actors/InteractableActors/Door.h"
#include "Components/StaticMeshComponent.h"
#include "Subsystems/Subsystem_EventManager.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(ActorMesh);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	USubsystem_EventManager* eventManagerptr = GetGameInstance()->GetSubsystem<USubsystem_EventManager>();

	if (eventManagerptr)
	{
		EventManager_Subsystem = eventManagerptr;
	}
	
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (CurveFloat)
	{
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleProgress"));
		DoorTimeline.AddInterpFloat(CurveFloat, ProgressFunction);
	}
	

	FOnTimelineEvent FinishedFunction;
	FinishedFunction.BindUFunction(this, FName("HandleFinished"));
	DoorTimeline.SetTimelineFinishedFunc(FinishedFunction);
}


void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	DoorTimeline.TickTimeline(DeltaTime);
	DotProductResult = CalculateDotProduct();

	IsDoorFree = CalculateIsDoorFree();

	
}

void ADoor::OpenTheDoor()
{
	UE_LOG(LogTemp, Warning, TEXT("OpenTheDoor called"))
	
	if (!IsPlaying)
	{
		if (FlipFlopVariable)
		{
			if (DotProductResult >= 0)
			{
				DoorEndFloat = -90.f;
				DoorTimeline.PlayFromStart();
			}
			else
			{
				DoorEndFloat = 90.f;
				DoorTimeline.PlayFromStart();
			}

			if (IsValid(DoorOpenSound) && IsValid(DoorSoundAttenuation))
			{
				FVector DoorLocation = GetActorLocation();
				UGameplayStatics::PlaySoundAtLocation(this, DoorOpenSound, DoorLocation, DoorSoundVolume, 1.f, 0.f, DoorSoundAttenuation);
			}

			FlipFlopVariable = false;
		}
		else
		{

			DoorTimeline.ReverseFromEnd();
			FlipFlopVariable = true;
		}
	}
}

float ADoor::CalculateDotProduct()
{
	if (PlayerCharacter)
	{
		FVector PlayerLocation = PlayerCharacter->GetActorLocation();
		FVector DoorLocation = GetActorLocation();
		FVector Door_FV = GetActorForwardVector();
		FVector NormalizedValue = PlayerLocation - DoorLocation;

		NormalizedValue.Normalize();
		float Result = FVector::DotProduct(Door_FV, NormalizedValue);

		return Result;
	}
	else
	{
		return 0.f;
	}
}



void ADoor::HandleProgress(float Value)
{
	float Rotation = FMath::Lerp(DoorStartFloat, DoorEndFloat, Value);

	FRotator  NewRotation(0.f,Rotation, 0.f);
	
	DoorMesh->SetRelativeRotation(NewRotation);

	IsPlaying = true;
}

void ADoor::HandleFinished()
{
	IsPlaying = false;

	if (FlipFlopVariable)
	{
		if (IsValid(DoorCloseSound) && IsValid(DoorSoundAttenuation))
		{
			FVector DoorLocation = GetActorLocation();
			UGameplayStatics::PlaySoundAtLocation(this, DoorCloseSound, DoorLocation, DoorSoundVolume, 1.f, 0.f, DoorSoundAttenuation);
		}
	}
}


bool ADoor::CalculateIsDoorFree()
{
	if (!RequireToWorkEvents.IsEmpty())
	{
		if (EventManager_Subsystem && EventManager_Subsystem->TriggeredEvents.HasAllExact(RequireToWorkEvents))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return true;
	}
}

void ADoor::InteractionTriggered_Implementation()
{
	Super::InteractionTriggered_Implementation();

	if (IsDoorFree)
	{
		OpenTheDoor();
	}
}
