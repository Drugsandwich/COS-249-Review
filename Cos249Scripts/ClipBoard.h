// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Math/Rotator.h"
#include "ClipBoard.generated.h"

UCLASS()
class COSROOM_API AClipBoard : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AClipBoard();

private:
	UPROPERTY(EditAnywhere, Category = "ClipBoard vars")
	float speed;
	UPROPERTY(EditAnywhere, Category = "ClipBoard vars")
	float rotSpeed;
	UPROPERTY(EditAnywhere, Category = "ClipBoard vars")
	AActor *playerComp;
	UInteractable *interactComp;
	FVector targetVec;
	FRotator boardRot;

	void InteractCheck();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
