// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "HeroController.h"
#include "GamePlayState.h"
#include "MonsterPaintingLogic.generated.h"

UCLASS()
class COSROOM_API AMonsterPaintingLogic : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMonsterPaintingLogic();
	void AnimEventKill();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UInteractable *interactComp;
	AHeroController *playerComp;
	AGamePlayState *gameState;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isFlipped;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isAwake;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float coolDown_awake;
	float currentCD_awake;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float coolDown;
	float currentCD;

	void Calculations();
	void InteractCheck();
};
