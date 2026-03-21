#include "Actors/BaseActors/InteractableActorBase.h"
#include "ActorComponents/AC_InteractionSystem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


AInteractableActorBase::AInteractableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	
	AC_InteractionSystem = CreateDefaultSubobject<UAC_InteractionSystem>(TEXT("Interaction System"));
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(DefaultSceneRoot);
}


void AInteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (AC_InteractionSystem)
	{
		AC_InteractionSystem->OnNPCInteract.AddDynamic(this, &AInteractableActorBase::InteractionTriggered);
	}
	
}


void AInteractableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableActorBase::InteractionTriggered_Implementation()
{
	
}

