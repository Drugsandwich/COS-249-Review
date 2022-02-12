// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HeroController.h"
#include "GamePlayState.h"
#include "DoorMonsterAI.generated.h"

UCLASS()
class COSROOM_API ADoorMonsterAI : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorMonsterAI();

	void ResetMonster();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vars", meta = (AllowPrivateAccess = "true"))
	bool doorHit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monster Vars", meta = (AllowPrivateAccess = "true"))
	bool isKilling;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float coolDownEnable;
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float currentEnableCD;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float attackCD;
	float currentAttackCD;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isAttackingDoor;
	int attacksDone;
	AActor *target;
	AHeroController *playerComp;

	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	FVector attackScaleVec;
	FVector normalScaleVec;

	float currentSpeed;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float slowSpeed;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float attackSpeed;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float distance;
	UPROPERTY(EditAnywhere, Category = "Monster Vars")
	float distanceToPlayer;

	UPROPERTY(EditAnywhere, Category = "MonsterPositions")
	AActor *doorPos;

	UPROPERTY(EditAnywhere, Category = "MonsterPositions")
	AActor *hidePos;

	UPROPERTY(EditAnywhere, Category = "MonsterPositions")
	AActor *playerPos;

	AGamePlayState *gameState;

	void CoolDownCheck();
	void DoorAttack();
	void ChaseTarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
