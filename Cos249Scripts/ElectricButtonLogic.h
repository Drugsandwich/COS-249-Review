// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "DoorMonsterAI.h"
#include "EngineUtils.h"
#include "GamePlayState.h"
#include "ElectricButtonLogic.generated.h"

UCLASS()
class COSROOM_API AElectricButtonLogic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AElectricButtonLogic();

	UFUNCTION(BlueprintCallable) // can be called in UI blueprint to show battery life
	float GetBatteryLife();
	void SetBatteryLife(float amount);

private:
	UInteractable *interactComp;
	AGamePlayState *gameState;

	UPROPERTY(EditAnywhere, Category = "Battery Stats")
	float batteryPerUse;
	UPROPERTY(EditAnywhere, Category = "Battery Stats")
	float maxBattery;
	UPROPERTY(EditAnywhere, Category = "Button vars")
	FVector usedPos;
	UPROPERTY(EditAnywhere, Category = "Button vars")
	AActor *electricFx;

	ADoorMonsterAI *monster;
	FVector activePos;
	float currentBattery;
	bool canBeUsed;
	FTimerHandle timeManager;

	UStaticMeshComponent *meshComp;
	UMaterialInstanceDynamic *dynamicMat;

	void InteractCheck();
	void BatteryCheck();
	void ResetButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
