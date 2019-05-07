// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Classes/Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"


UCLASS()
class BATTERYTUTORIAL_API APickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//true when battery can be used, false when deactivated
	bool bIsActive;


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	//return the mesh for the pickup
	FORCEINLINE class UStaticMeshComponent * GetMesh() const { return PickupMesh; }

	//returns if the battery is active
	UFUNCTION(BlueprintPure, Category = "Pickup")
	bool isActive();

	//changes the state of the battery
	UFUNCTION(BlueprintCallable, Category = "Pickup")
	void setActive(bool NewPickupState);

	UFUNCTION(BlueprintNativeEvent)
	void WasCollected();

	virtual void WasCollected_Implementation();

private:
	//static mesh to represent pickup in the level
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent * PickupMesh;
	
};
