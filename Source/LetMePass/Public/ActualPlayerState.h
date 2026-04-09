#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ActualPlayerState.generated.h"


UCLASS()
class LETMEPASS_API AActualPlayerState : public APlayerState
{
	GENERATED_BODY()

	
protected:
	
	virtual void BeginPlay() override;

public:

	AActualPlayerState();
	virtual void Tick(float DeltaTime) override;

	//VARIABLES!!!
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RoomStateNumber{1};

	UPROPERTY()
	ACharacter* PlayerCharacter;

	//FUNCTIONS!!!
public:

	UFUNCTION()
	void FindingPlayerRoomState();
	
};
