// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "ElectricButtonLogic.h"

// Sets default values
AElectricButtonLogic::AElectricButtonLogic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AElectricButtonLogic::BeginPlay()
{
	Super::BeginPlay();

	meshComp = FindComponentByClass<UStaticMeshComponent>();
	dynamicMat = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this); // create dynamic mat by storing existing one so we can change its values
	meshComp->SetMaterial(0, dynamicMat);										   // set mesh with the dynamic mat instance

	interactComp = FindComponentByClass<UInteractable>();
	gameState = Cast<AGamePlayState>(UGameplayStatics::GetActorOfClass(GetWorld(), AGamePlayState::StaticClass()));
	currentBattery = maxBattery;

	canBeUsed = true;
	activePos = GetActorLocation();

	for (TActorIterator<ADoorMonsterAI> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator) // iterator to get the monster component
	{
		monster = *ActorIterator;
		break;
	}
}

//Function taht is responsible for reseting the button and electricity fx
void AElectricButtonLogic::ResetButton()
{
	SetActorLocation(activePos); // set actor posiiton as active
	interactComp->SetInteract(false);
	dynamicMat->SetScalarParameterValue("Emission Multiplier", 2.0f);
	electricFx->GetRootComponent()->ToggleVisibility(true);
	canBeUsed = true;
}

//Function that is responsible of keeping track if player has interacted with the button
void AElectricButtonLogic::InteractCheck()
{
	// if the button is used set electicity fx to true and reset monster and take battery life
	if (interactComp->GetInteract() && canBeUsed && currentBattery > 0.0f)
	{
		SetActorLocation(activePos - usedPos); // set actor position as used
		currentBattery -= batteryPerUse;
		canBeUsed = false;
		dynamicMat->SetScalarParameterValue("Emission Multiplier", 0.1f);									 // set button to lower emission color
		electricFx->GetRootComponent()->ToggleVisibility(true);												 // set fx to true
		monster->ResetMonster();																			 // reset monster
		GetWorldTimerManager().SetTimer(timeManager, this, &AElectricButtonLogic::ResetButton, 2.0f, false); // reset button and fx
	}
}

//Function taht checks the battery life left
void AElectricButtonLogic::BatteryCheck()
{
	if (currentBattery <= 0.f) // if battery is equal or less then 0 then set button is not usable
	{
		dynamicMat->SetScalarParameterValue("Emission Multiplier", 0.1f); // change color of button to gray
		currentBattery = 0.f;
		canBeUsed = false;
	}
}

//Function that can be used outside this script to check the current battery life left
float AElectricButtonLogic::GetBatteryLife()
{
	return currentBattery;
}

//Function taht can be called outside this script to modify the battery amount
void AElectricButtonLogic::SetBatteryLife(float amount)
{
	currentBattery -= amount;
}

// Called every frame
void AElectricButtonLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BatteryCheck();
	if (gameState->GetIsPlaying())
	{
		InteractCheck();
	}
}
