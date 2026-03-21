#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActorBase.generated.h"

class UAC_InteractionSystem;
class UStaticMeshComponent;
class USceneComponent;

UCLASS()
class LETMEPASS_API AInteractableActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AInteractableActorBase();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	// VARIABLES!!!
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor Components")
	UAC_InteractionSystem* AC_InteractionSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ActorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	
	// FUNCTIONS!!!
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void InteractionTriggered();

	virtual void InteractionTriggered_Implementation();
};
