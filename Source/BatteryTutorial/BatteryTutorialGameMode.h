// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BatteryTutorialGameMode.generated.h"

//enum to store current state of game
UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPLAYING,
	EGAMEOVER,
	EWON,
	EUNKNOWN
};


UCLASS(minimalapi)
class ABatteryTutorialGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABatteryTutorialGameMode();
	virtual void Tick(float DeltaTime) override;

	//returns power needed to win, needed by the HUD
	UFUNCTION(BlueprintPure, Category = "Power")
		float GetPowerToWin() const { return PowerToWin; }

	virtual void BeginPlay() override;

	//getter for game state
	UFUNCTION(BlueprintPure, Category = "Power")
		EBatteryPlayState GetCurrentState() const;

	//set a new play state
	void SetCurrentState(EBatteryPlayState NewState);



protected:
	//the rate at which the character loses power
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float DecayRate;

	//amount of power required to win the game
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		float PowerToWin;

	//Widget class used for our HUD
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	//instance of the HUD
	UPROPERTY()
		class UUserWidget * CurrentWidget;


private:
	//keeps track of current play state
	EBatteryPlayState CurrentState;

	//array of spawn volumes
	TArray<class ASpawnVolume *> SpawnVolumeActors;

	//handle any function calls that rely upon changing the state in the game
	void HandleNewState(EBatteryPlayState NewState);
};



