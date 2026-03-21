#include "Actors/BaseActors/TalkableActorBase.h"
#include "ActorComponents/AC_DialogueSystem.h"

ATalkableActorBase::ATalkableActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AC_DialogueSystem = CreateDefaultSubobject<UAC_DialogueSystem>(TEXT("Dialogue System"));
}

void ATalkableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATalkableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
