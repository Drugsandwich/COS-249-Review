// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "HeroController.h"
#include "GamePlayState.generated.h"

UCLASS()
class COSROOM_API AGamePlayState : public AActor
{
	GENERATED_BODY()

private:
	UTextRenderComponent *txtTime;
	AHeroController *heroComp;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isPlaying; // bool that is set after tutorial
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool isPaused; // bool that is set or stopped when pausing the game
	UPROPERTY(EditAnywhere, Category = "Game Vars")
	float startTime;
	float currentT;

	void TimeCalculate();

public:
	// Sets default values for this actor's properties
	AGamePlayState();
	bool GetIsPlaying();
	bool GetIsPaused();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
