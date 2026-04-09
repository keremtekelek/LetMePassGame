#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Engine/LevelStreaming.h"
#include "LevelStreamingHandler.generated.h"

class ALetMePassCharacter;
class AActualPlayerState;


UCLASS()
class LETMEPASS_API ALevelStreamingHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ALevelStreamingHandler();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

	//VARIABLES!!!
public:

	UPROPERTY()
	ALetMePassCharacter* MainCharacter;

	UPROPERTY()
	AActualPlayerState* PlayerState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int, ATriggerBox*> RoomID_TriggerBoxMap;

	

	
	


	//FUNCTIONS!!
public:
	
	UFUNCTION()
	void GettingVariables();

	UFUNCTION()
	void OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
