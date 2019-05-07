// Fill out your copyright notice in the Description page of Project Settings.

#include "Pickup.h"


// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	bIsActive = true;

	//create the static mesh component
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;

}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
}

bool APickup::isActive()
{
	return bIsActive;
}

void APickup::setActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}


// Called every frame
//void APickup::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void APickup::WasCollected_Implementation()
{
	//log a debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You have collected %s"), *PickupDebugString);
}