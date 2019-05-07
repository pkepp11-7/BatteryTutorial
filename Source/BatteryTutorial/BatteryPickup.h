// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class BATTERYTUTORIAL_API ABatteryPickup : public APickup
{
	GENERATED_BODY()
public:

	// Sets default values for this actor's properties
	ABatteryPickup();
	void WasCollected_Implementation() override;

	//accessor to battery power
	float GetPower() { return BatteryPower; }
	
protected:
	//set the amount of power the battery gives to player
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float BatteryPower;
};
