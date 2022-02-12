// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/Character.h"
#include "GenericPlatform/ICursor.h"
#include "Interactable.h"
#include "HeroController.generated.h"

UCLASS()
class COSROOM_API AHeroController : public ACharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent *cam;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float maxRot;
	UPROPERTY(EditAnywhere, Category = "Camera")
	float smoothRot;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isDead;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isWin;

	UWorld *m_world;
	APlayerController *p_controller;
	FInputModeGameOnly inputData;
	float mouseX;
	float mouseY;
	FVector2D mouseVecPos;

	float yawRot;
	FVector startRay;
	FVector endRay;

	UInteractable *interactable_obj;

	void InteractInput();
	void HorizRot(float value);
	void InteractionCheck();
	void ChangeCursor(bool isInteractable);

public:
	// Sets default values for this character's properties
	AHeroController();
	void SetIsDead(bool state);
	void SetIsWinning(bool state);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;
};
