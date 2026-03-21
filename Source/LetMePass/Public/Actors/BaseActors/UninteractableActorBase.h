#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UninteractableActorBase.generated.h"

class UStaticMeshComponent;
class USceneComponent;


UCLASS()
class LETMEPASS_API AUninteractableActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AUninteractableActorBase();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	
	// VARIABLES!!!
public:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ActorMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* DefaultSceneRoot;
	
	
	// FUNCTIONS!!!
public:
	
	

};
