#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActors/InteractableActorBase.h"
#include "TalkableActorBase.generated.h"

class UAC_InteractionSystem;
class UAC_DialogueSystem;

UCLASS()
class LETMEPASS_API ATalkableActorBase : public AInteractableActorBase
{
	GENERATED_BODY()
	
	ATalkableActorBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	// VARIABLES!!!
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components")
	UAC_DialogueSystem* AC_DialogueSystem;
	
	
	// FUNCTIONS!!!
public:
	
};
