// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "MonsterPaintingLogic.h"
#include "Components/WidgetComponent.h"

// Sets default values
AMonsterPaintingLogic::AMonsterPaintingLogic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMonsterPaintingLogic::BeginPlay()
{
	Super::BeginPlay();
	interactComp = FindComponentByClass<UInteractable>();

	currentCD = coolDown;
	currentCD_awake = coolDown_awake;
	playerComp = Cast<AHeroController>(UGameplayStatics::GetActorOfClass(GetWorld(), AHeroController::StaticClass()));
	gameState = Cast<AGamePlayState>(UGameplayStatics::GetActorOfClass(GetWorld(), AGamePlayState::StaticClass()));
}

//This function is being called form the animator of the monster it is responsible for killling the player
void AMonsterPaintingLogic::AnimEventKill()
{
	//set player death
	playerComp->SetIsDead(true);
}

//Function that calculates the cool down on awake and normal cool down on attack
void AMonsterPaintingLogic::Calculations()
{
	currentCD_awake -= FApp::GetDeltaTime();

	if (currentCD_awake <= 0.0f) // if awake cooldown is less or equal to 0 then reset the painting
	{
		isFlipped = false; // flip back painting
		currentCD -= FApp::GetDeltaTime();

		if (currentCD <= 0.0f) // if cooldown is equal or less then 0 then set the painting to awake (attacking)
		{
			isAwake = true;
		}
		else // else painting is not attacking
		{
			isAwake = false;
		}
	}
}

//This function checks if the player is interacting with the painting
void AMonsterPaintingLogic::InteractCheck()
{
	// if monster cooldown is down (active) and player is interacting then flip painting and reset monster
	if (interactComp->GetInteract() && currentCD <= 0.0f)
	{
		//flip the painting
		isFlipped = true;
		interactComp->SetInteract(false);
		currentCD = coolDown;
		currentCD_awake = coolDown_awake;
	}
	else
	{
		interactComp->SetInteract(false);
	}
}

// Called every frame
void AMonsterPaintingLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (gameState->GetIsPlaying())
	{
		InteractCheck();
		Calculations();
	}
}
