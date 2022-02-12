// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "GenericPlatform/GenericPlatformMath.h"
#include "GamePlayState.h"

// Sets default values
AGamePlayState::AGamePlayState()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGamePlayState::BeginPlay()
{
	Super::BeginPlay();
	heroComp = Cast<AHeroController>(UGameplayStatics::GetActorOfClass(GetWorld(), AHeroController::StaticClass()));
	txtTime = FindComponentByClass<UTextRenderComponent>();
	currentT = startTime;
	txtTime->SetText(FString::FromInt((int32)currentT));
}

//function responsible to change the time and set win condition
void AGamePlayState::TimeCalculate()
{
	if (isPlaying && !isPaused)
	{
		if (currentT <= 0.f) // if there is no more time then set game in win state
		{
			heroComp->SetIsWinning(true);
			txtTime->SetText(FString::FromInt(0));
		}
		else // else keep ticking time
		{
			currentT -= FApp::GetDeltaTime();
			txtTime->SetText(FString::FromInt((int32)currentT));
		}
	}
}

bool AGamePlayState::GetIsPlaying()
{
	return isPlaying;
}

bool AGamePlayState::GetIsPaused()
{
	return isPaused;
}

// Called every frame
void AGamePlayState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeCalculate();
}
