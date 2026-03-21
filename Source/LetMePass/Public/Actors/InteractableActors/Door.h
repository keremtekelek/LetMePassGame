#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseActors/InteractableActorBase.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TimelineComponent.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundAttenuation.h"
#include "GameFramework/Character.h"
#include "Door.generated.h"


class UStaticMeshComponent;

UCLASS()
class LETMEPASS_API ADoor : public AInteractableActorBase
{
	GENERATED_BODY()
	
	ADoor();
	
protected:
	
	virtual void BeginPlay() override;
	virtual void InteractionTriggered_Implementation() override;
	virtual void Tick(float DeltaTime) override;
	
	//VARIABLES
public:
	
	UPROPERTY(VisibleAnywhere)
	ACharacter* PlayerCharacter;
	
	UPROPERTY(VisibleAnywhere)
	bool CanInteract = false;

	UPROPERTY(VisibleAnywhere)
	bool IsDoorOpen = false;

	UPROPERTY(VisibleAnywhere)
	bool IsPlaying = false;

	UPROPERTY(VisibleAnywhere)
	bool FlipFlopVariable = true;

	UPROPERTY(VisibleAnywhere)
	float DotProductResult = 0.f;

	UPROPERTY(VisibleAnywhere)
	float DoorStartFloat = 0.f;

	UPROPERTY(VisibleAnywhere)
	float DoorEndFloat = 90.f;

	UPROPERTY(EditAnywhere)
	float DoorSoundVolume = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DoorOpenSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* DoorCloseSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundAttenuation* DoorSoundAttenuation;

	UPROPERTY()
	FTimeline DoorTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* DoorMesh;
	
	//FUNCTIONS
public:
	
	UFUNCTION()
	void OpenTheDoor();

	UFUNCTION()
	float CalculateDotProduct();

	UFUNCTION()
	void HandleProgress(float Value);

	UFUNCTION()
	void HandleFinished();

};
