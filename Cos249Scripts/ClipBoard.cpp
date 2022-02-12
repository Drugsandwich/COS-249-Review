// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "ClipBoard.h"

// Sets default values
AClipBoard::AClipBoard()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AClipBoard::BeginPlay()
{
	Super::BeginPlay();
	interactComp = FindComponentByClass<UInteractable>();
}

void AClipBoard::InteractCheck()
{
	if (interactComp->GetInteract())
	{
		boardRot = FMath::RInterpConstantTo(GetActorRotation(), playerComp->GetActorRotation(), FApp::GetDeltaTime(), rotSpeed);
		targetVec = FMath::VInterpConstantTo(GetActorLocation(), playerComp->GetActorLocation(), FApp::GetDeltaTime(), speed);
		SetActorRotation(boardRot);
		SetActorLocation(targetVec);
	}
}

// Called every frame
void AClipBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	InteractCheck();
}
