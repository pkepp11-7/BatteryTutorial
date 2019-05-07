// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Classes/Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class BATTERYTUTORIAL_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//The pickup to spawn
	UPROPERTY(EditAnywhere, Category = "Spawning")
	TSubclassOf<class APickup> WhatToSpawn;

	FTimerHandle SpawnTimer;

	//Minimum Spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeLow;
	//Maximum spawn Delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SpawnDelayRangeHigh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//returns WhereToSpawn subobject
	FORCEINLINE class UBoxComponent * GetWhereToSpawn() const { return WhereToSpawn; }
	
	UFUNCTION(BlueprintPure, Category = "Spawning")
	FVector GetRandomPointInVolume();

	//toggles spawning
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SetSpawiningActive(bool SpawningActive);

private:
	//Box component to determine where pickups should spawn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent * WhereToSpawn;

	//handle spawning a new pickup
	void SpawnPickup();

	//The current spawn delay
	float SpawnDelay;
};
