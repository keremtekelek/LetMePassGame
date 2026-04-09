#include "ActualPlayerState.h"
#include "GameFramework/Character.h"

AActualPlayerState::AActualPlayerState()
{
	PrimaryActorTick.bCanEverTick = true;

	this->SetActorTickInterval(0.5f);
}

void AActualPlayerState::BeginPlay()
{
	Super::BeginPlay();

	this->SetActorTickInterval(0.5);
	
	ACharacter* PC = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (PC)
	{
		PlayerCharacter = PC;
	}
}



void AActualPlayerState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FindingPlayerRoomState();
	
}

void AActualPlayerState::FindingPlayerRoomState()
{
	FVector Start = PlayerCharacter->GetActorLocation();
	FVector End = PlayerCharacter->GetActorLocation() + FVector(0, 0, -250);
	FHitResult HitResult;
	FCollisionQueryParams  COQP;
	COQP.AddIgnoredActor(PlayerCharacter);						
	FCollisionResponseParams CollRes;
			
	
			
	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility, COQP, CollRes))
	{
		AActor* HitActor = HitResult.GetActor();
		
		if (HitActor)
		{
			for (const FName& t : HitActor->Tags)
			{
				int tempInt = UKismetStringLibrary::Conv_StringToInt(t.ToString());

				RoomStateNumber = tempInt;
			}

			AActor* ParentActor = HitActor->GetAttachParentActor();
			if (ParentActor)
			{
				for (const FName& t : ParentActor->Tags)
				{
					int tempInt = UKismetStringLibrary::Conv_StringToInt(t.ToString());
					RoomStateNumber = tempInt;
				}
			}
		}
		else
		{
			DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, 0.5f, 0, 2.0f);
		}
	}
}
