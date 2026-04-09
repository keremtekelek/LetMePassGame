#include "LevelStreaming/LevelStreamingHandler.h"
#include "LetMePassCharacter.h"
#include "GameFramework/Character.h"
#include "ActualPlayerState.h"


ALevelStreamingHandler::ALevelStreamingHandler()
{
	PrimaryActorTick.bCanEverTick = false;

}


void ALevelStreamingHandler::BeginPlay()
{
	Super::BeginPlay();

	GettingVariables();

	
	for (auto& Pair : RoomID_TriggerBoxMap)
	{
		ATriggerBox* CurrentTriggerBox = Pair.Value;

		if (CurrentTriggerBox)
		{
			CurrentTriggerBox->OnActorBeginOverlap.AddDynamic(this, &ALevelStreamingHandler::OnTriggerBeginOverlap);

			UE_LOG(LogTemp, Warning, TEXT("TriggeredBox is valid"))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("TriggeredBox is not valid"))
		}
	}
	
}


void ALevelStreamingHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelStreamingHandler::GettingVariables()
{
	ACharacter* PC = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PC)
	{
		MainCharacter = Cast<ALetMePassCharacter>(PC);
	}

	AActualPlayerState* PS = MainCharacter->GetPlayerState<AActualPlayerState>();

	if (PS)
	{
		PlayerState = PS;
		
	}
}

void ALevelStreamingHandler::OnTriggerBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("MainCharacter"))
	{
		ATriggerBox* TriggeredBox = Cast<ATriggerBox>(OverlappedActor);
		const int* TriggeredBoxKeyPTR = RoomID_TriggerBoxMap.FindKey(TriggeredBox);

		int TriggeredBoxKey = *TriggeredBoxKeyPTR;

		int CurrentPlayerRoomState = PlayerState->RoomStateNumber;

		FString DebugMessage = FString::Printf(TEXT("Triggered Box Number: %d | Current Player Room State: %d"), TriggeredBoxKey, CurrentPlayerRoomState);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, DebugMessage);
		
		if (CurrentPlayerRoomState == TriggeredBoxKey)
		{
			FString tempStr = FString("Level") + UKismetStringLibrary::Conv_IntToString(PlayerState->RoomStateNumber + 1);
			FName NextLevelName = FName(*tempStr);

			ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), NextLevelName);

			if (StreamingLevel)
			{
				if (StreamingLevel->IsLevelLoaded())
				{
					
				}
				else
				{
					UGameplayStatics::LoadStreamLevel(GetWorld(), NextLevelName, true, false, FLatentActionInfo());
				}
			}
			else
			{
				FString ErrorMsg = FString::Printf(TEXT(" %s named sub-level does not exist! "), *tempStr);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMsg);
			}
		}
		else
		{
			FString tempStr = FString("Level") + UKismetStringLibrary::Conv_IntToString(PlayerState->RoomStateNumber - 1);
			FName NextLevelName = FName(*tempStr);

			ULevelStreaming* StreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), NextLevelName);

			if (StreamingLevel)
			{
				if (StreamingLevel->IsLevelLoaded())
				{
					
				}
				else
				{
					UGameplayStatics::LoadStreamLevel(GetWorld(), NextLevelName, true, false, FLatentActionInfo());
				}
			}
			else
			{
				FString ErrorMsg = FString::Printf(TEXT("%s named sub-level does not exist!"), *tempStr);
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, ErrorMsg);
			}
		}
	}
}

