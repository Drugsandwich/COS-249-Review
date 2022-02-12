// Fill out your copyright notice in the Description page of Project Settings.

#include "HeroController.h"

// Sets default values
AHeroController::AHeroController()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cam->AttachTo(RootComponent);
	cam->SetRelativeLocation(FVector(0, 0, 40));
}

// Called when the game starts or when spawned
void AHeroController::BeginPlay()
{
	Super::BeginPlay();
	m_world = GetWorld(); // set world

	p_controller = m_world->GetFirstPlayerController(); // get controller
	p_controller->bShowMouseCursor = true;				// show mouse
	inputData.SetConsumeCaptureMouseDown(false);		// disable consume mouse down
	p_controller->SetInputMode(inputData);				// feed the over ridden to
}

//function that is being called when the player input the interact key (default mouse0)
void AHeroController::InteractInput()
{
	if (interactable_obj != nullptr) // if the interactable object is not null then set it as used
	{
		interactable_obj->SetInteract(true);
	}
}

//Function that changes the cursor from default arrow  to hand and back showing that you can interact with the hovered actor
void AHeroController::ChangeCursor(bool isInteractable)
{
	if (isInteractable)
	{
		p_controller->CurrentMouseCursor = EMouseCursor::Type::Hand;
	}
	else
	{
		p_controller->CurrentMouseCursor = EMouseCursor::Type::Default;
	}
}

//Function that shoots a raycast from the mouse position and check if the actor is interactable or not
void AHeroController::InteractionCheck()
{
	p_controller->GetMousePosition(mouseX, mouseY);
	mouseVecPos.X = mouseX;
	mouseVecPos.Y = mouseY;
	FHitResult hitResult;

	if (p_controller->GetHitResultAtScreenPosition(mouseVecPos, ECC_Visibility, false, hitResult))
	{
		if (hitResult.GetActor() != nullptr)
		{
			if (hitResult.GetActor()->ActorHasTag("Interactable")) // if actor is with tag interactable set the cursor and set the interactable obj
			{
				ChangeCursor(true); // set cursor type to hand
				interactable_obj = hitResult.GetActor()->FindComponentByClass<UInteractable>();
			}
			else
			{
				interactable_obj = nullptr;
				ChangeCursor(false); // set cursor type arrow
			}
		}
		else
		{
			interactable_obj = nullptr;
		}
	}
	else
	{
		interactable_obj = nullptr;
		ChangeCursor(false); // set cursor type arrow
	}
}

//function that is being called when the horizontal variable is changed from player input
void AHeroController::HorizRot(float value)
{
	if (value)
	{
		yawRot = cam->GetRelativeRotation().Yaw + value; // get curret YawRot value

		if (yawRot < maxRot && yawRot > -maxRot)
		{
			cam->AddLocalRotation(FRotator(0, value * smoothRot * m_world->GetDeltaSeconds(), 0)); // move the camera with smooth
		}
	}
}

//Function that can be used out of this script to change the state of the player to dead or alive
void AHeroController::SetIsDead(bool state)
{
	isDead = state;
}

//Function that can be used out of this script to change the state of the player to win or not
void AHeroController::SetIsWinning(bool state)
{
	isWin = state;
}

// Called every frame
void AHeroController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AHeroController::InteractionCheck();
}

// Called to bind functionality to input
void AHeroController::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InputComponent->BindAxis("HoriRot", this, &AHeroController::HorizRot);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AHeroController::InteractInput);
}
