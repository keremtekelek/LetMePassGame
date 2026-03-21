#include "Actors/BaseActors/UninteractableActorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"


AUninteractableActorBase::AUninteractableActorBase()
{
 	PrimaryActorTick.bCanEverTick = false;
	
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Scene Root"));
	RootComponent = DefaultSceneRoot;
	
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Actor Mesh"));
	ActorMesh->SetupAttachment(DefaultSceneRoot);

}


void AUninteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AUninteractableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

