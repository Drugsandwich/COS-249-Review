// Fill out your copyright notice in the Description page of Project Settings.
#include "Interactable.h"

// Sets default values for this component's properties
UInteractable::UInteractable()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UInteractable::BeginPlay()
{
	Super::BeginPlay();
	// ...
}

//function that can be called out of this script to change if the object is being interacted to or not
void UInteractable::SetInteract(bool isInteracted)
{
	isUsed = isInteracted;
}

//Function that can be called out of this script to return if this object is interacted with or not
bool UInteractable::GetInteract()
{
	return isUsed;
}

// Called every frame
void UInteractable::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
