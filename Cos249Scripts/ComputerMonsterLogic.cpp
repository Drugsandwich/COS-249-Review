// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "Components/WidgetComponent.h"
#include "ComputerMonsterLogic.h"

// Sets default values
AComputerMonsterLogic::AComputerMonsterLogic()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AComputerMonsterLogic::BeginPlay()
{
	Super::BeginPlay();
	idleUI = Cast<UWidgetComponent>(GetDefaultSubobjectByName("idleUI"));
	miniGameUI = Cast<UWidgetComponent>(GetDefaultSubobjectByName("MiniGameUI"));
	meshComp = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName("ButtonMesh"));
	dynamicMat = UMaterialInstanceDynamic::Create(meshComp->GetMaterial(0), this);
	meshComp->SetMaterial(0, dynamicMat);

	batteryComp = Cast<AElectricButtonLogic>(UGameplayStatics::GetActorOfClass(GetWorld(), AElectricButtonLogic::StaticClass()));
	gameState = Cast<AGamePlayState>(UGameplayStatics::GetActorOfClass(GetWorld(), AGamePlayState::StaticClass()));
	interactComp = FindComponentByClass<UInteractable>();

	can_changeStage = true;
	currentCD = coolDown;
}

//Function that is respnsible for doing caculations on cooldown and setting up UI
void AComputerMonsterLogic::Calculate()
{
	currentCD -= FApp::GetDeltaTime();

	if (currentCD < 0.f) //if its off cooldown then start draining battery and set UI minigame visible and hite the idle UI on monster
	{
		batteryComp->SetBatteryLife(batteryDrainRate * FApp::GetDeltaTime());
		miniGameUI->SetVisibility(true);
		idleUI->SetVisibility(false);
	}
	else // else make emissioncolor to gray and hide the minigame ui and set visible the idleUI on monster
	{
		dynamicMat->SetVectorParameterValue("EmissionColor", FLinearColor::Gray);
		miniGameUI->SetVisibility(false);
		idleUI->SetVisibility(true);
	}
}

//Function that is called on timer from StageChanger
//This function is responsible for changing the stage
void AComputerMonsterLogic::NextStage()
{
	can_changeStage = true;
	buttonStage++;

	if (buttonStage > 2) //reset stage
	{
		buttonStage = 0;
	}
}

//Function taht is respnsible for changing the stage of the button and its emssion material color
void AComputerMonsterLogic::StageChanger()
{
	if (can_changeStage && currentCD < 0.f) //if can change stage and monster is active then execute
	{
		switch (buttonStage) // depending on the stage change the color and set a timer for next stage method call
		{
		case 0:
			dynamicMat->SetVectorParameterValue("EmissionColor", FLinearColor::Red);
			GetWorldTimerManager().SetTimer(timeManager, this, &AComputerMonsterLogic::NextStage, 2.0f, false);
			can_changeStage = false;
			break;
		case 1:
			dynamicMat->SetVectorParameterValue("EmissionColor", FLinearColor::Yellow);
			GetWorldTimerManager().SetTimer(timeManager, this, &AComputerMonsterLogic::NextStage, 2.0f, false);
			can_changeStage = false;
			break;
		case 2:
			dynamicMat->SetVectorParameterValue("EmissionColor", FLinearColor::Green);
			GetWorldTimerManager().SetTimer(timeManager, this, &AComputerMonsterLogic::NextStage, 2.0f, false);
			can_changeStage = false;
			break;
		}
	}
}

//Function that is responsible for checking the stage and how many correct clicks are done
void AComputerMonsterLogic::StageCheck()
{
	if (buttonStage == 2) // if button is on stage 2 green then its a correct click
	{
		correctClicks++;
		NextStage();
	}
	else //else then take battery life as its false
	{
		batteryComp->SetBatteryLife(failBatteryDrain);
	}

	if (correctClicks >= 3) // if there is 3 or more correct clicks then set the monster on cool down
	{
		correctClicks = 0;
		currentCD = coolDown;
	}
}

//Function that is responsilbe for the interaction check
void AComputerMonsterLogic::InteractCheck()
{
	// if player has clicked the button and is off cooldown then reset interaction and check the button stage
	if (interactComp->GetInteract() && currentCD < 0.f)
	{
		StageCheck();
		interactComp->SetInteract(false);
	}
	else // else the button is still unactive so just restart the interaction
	{
		interactComp->SetInteract(false);
	}
}

// Called every frame
void AComputerMonsterLogic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (gameState->GetIsPlaying())
	{
		Calculate();
		InteractCheck();
		StageChanger();
	}
}
