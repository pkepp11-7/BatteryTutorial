// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"


// Sets default values for this actor's properties
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);
	BatteryPower = 150.0f;
}

//override the Pickup WasCollected function
void ABatteryPickup::WasCollected_Implementation()
{
	//use base pickup behavior
	Super::WasCollected_Implementation();

	//destroy the battery
	Destroy();

}

