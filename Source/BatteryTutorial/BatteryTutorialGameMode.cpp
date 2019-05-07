// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "BatteryTutorialGameMode.h"
#include "BatteryTutorialCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Classes/Components/SkeletalMeshComponent.h"

#include "SpawnVolume.h"
ABatteryTutorialGameMode::ABatteryTutorialGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//required for tick to be called
	PrimaryActorTick.bCanEverTick = true;

	//set default decay rate
	DecayRate = 0.01f;

}

void ABatteryTutorialGameMode::BeginPlay()
{
	Super::BeginPlay();

	//find all spawn volume actors
	TArray<AActor *> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (int iActor = 0; iActor < FoundActors.Num(); iActor++)
	{
		ASpawnVolume * SpawnVolumeActor = Cast<ASpawnVolume>(FoundActors[iActor]);
		if (SpawnVolumeActor != nullptr)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	//Set starting state to playing
	SetCurrentState(EBatteryPlayState::EPLAYING);

	//set the score to beat
	ABatteryTutorialCharacter * MyCharacter = Cast<ABatteryTutorialCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter != nullptr)
	{
		PowerToWin = MyCharacter->GetInitialPower() * 1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	
}


void ABatteryTutorialGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//get
	ABatteryTutorialCharacter * MyCharacter = Cast<ABatteryTutorialCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	//check for successful cast
	if (MyCharacter != nullptr)
	{
		//check winning condition
		if (MyCharacter->GetCharacterPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWON);
		}

		//reduce player power by a set amount each tick if player still has power
		else if (MyCharacter->GetCharacterPower() > 0)
		{
			MyCharacter->UpdatePower(-DecayRate * DeltaTime * (MyCharacter->GetInitialPower()));
		}

		else if (MyCharacter->GetCharacterPower() <= 0)
		{
			SetCurrentState(EBatteryPlayState::EGAMEOVER);
		}
	}
}

//getter for game state
EBatteryPlayState ABatteryTutorialGameMode::GetCurrentState() const
{
	return CurrentState;
}

//set a new play state
void ABatteryTutorialGameMode::SetCurrentState(EBatteryPlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(NewState);
}

//handle any function calls that rely upon changing the state in the game
void ABatteryTutorialGameMode::HandleNewState(EBatteryPlayState NewState)
{
	APlayerController * PlayerController;
	ACharacter * MyCharacter;

	switch (NewState)
	{
		//game is playing
	case EBatteryPlayState::EPLAYING:
		//spawn volumes are active
		for (int iSpawner = 0; iSpawner < SpawnVolumeActors.Num(); iSpawner++)
		{
			SpawnVolumeActors[iSpawner]->SetSpawiningActive(true);
		}
		break;

		//game is lost
	case EBatteryPlayState::EGAMEOVER:
		///disable input
		PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController != nullptr)
		{
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		//deactivate spawn volumes
		for (int iSpawner = 0; iSpawner < SpawnVolumeActors.Num(); iSpawner++)
		{
			SpawnVolumeActors[iSpawner]->SetSpawiningActive(false);
		}
		//ragdoll character
		MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter != nullptr)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
		break;
		
		//game is won
	case EBatteryPlayState::EWON:
		//deactivate spawn volumes
		for (int iSpawner = 0; iSpawner < SpawnVolumeActors.Num(); iSpawner++)
		{
			SpawnVolumeActors[iSpawner]->SetSpawiningActive(false);
		}
		break;
	default:
		//do nothing
		break;
	}
}