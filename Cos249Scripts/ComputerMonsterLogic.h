// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "ElectricButtonLogic.h"
#include "Components/WidgetComponent.h"
#include "GamePlayState.h"
#include "ComputerMonsterLogic.generated.h"

UCLASS()
class COSROOM_API AComputerMonsterLogic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AComputerMonsterLogic();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UInteractable *interactComp;
	UStaticMeshComponent *meshComp;
	UMaterialInstanceDynamic *dynamicMat;
	AElectricButtonLogic *batteryComp;
	UWidgetComponent *idleUI;
	UWidgetComponent *miniGameUI;
	FTimerHandle timeManager;
	AGamePlayState *gameState;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float coolDown;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float currentCD;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int correctClicks;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float batteryDrainRate;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float failBatteryDrain;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int buttonStage;
	bool can_changeStage;

	void StageCheck();
	void StageChanger();
	void InteractCheck();
	void Calculate();
	void NextStage();
};
