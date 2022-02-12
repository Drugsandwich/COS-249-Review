// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "Containers/Array.h"
#include "DoorMonsterAI.h"

// Sets default values
ADoorMonsterAI::ADoorMonsterAI()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoorMonsterAI::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(hidePos->GetActorLocation()); // set location of monster to hide pos
	target = hidePos;							   // set default target to hide position
	currentSpeed = slowSpeed;					   // set speed to slow
	currentEnableCD = coolDownEnable;
	currentAttackCD = attackCD;
	normalScaleVec = GetActorScale3D();
	playerComp = Cast<AHeroController>(UGameplayStatics::GetActorOfClass(GetWorld(), AHeroController::StaticClass()));
	gameState = Cast<AGamePlayState>(UGameplayStatics::GetActorOfClass(GetWorld(), AGamePlayState::StaticClass()));
}

//function that moves the monster to its target with speed that is changed through out the code
void ADoorMonsterAI::ChaseTarget()
{
	distance = FVector::Distance(GetActorLocation(), target->GetActorLocation());
	distanceToPlayer = FVector::Distance(GetActorLocation(), playerPos->GetActorLocation());
	SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), target->GetActorLocation(), FApp::GetDeltaTime(), currentSpeed));
}

//Function taht is responsible of cooldown check and setting up the target
void ADoorMonsterAI::CoolDownCheck()
{
	currentEnableCD -= FApp::GetDeltaTime();

	//if enable cooldown is less then 0 and is not attacking and attack cd is more then 0 then start ticking off the attackCD and make the monster go to door
	if (currentEnableCD < 0 && currentAttackCD > 0 && !isAttackingDoor)
	{
		currentAttackCD -= FApp::GetDeltaTime();
		target = doorPos;
	}

	//if cooldown on attack less then 0 then attack the door and set doorhit as true for the door animation to player
	if (currentAttackCD < 0)
	{
		isAttackingDoor = true;
		doorHit = true;
	}
}

//function that checks if monster is close to atttackign the door and keeps track of how many attacks are done
void ADoorMonsterAI::DoorAttack()
{
	if (isAttackingDoor) // if is attacking door then size up the monster
	{
		SetActorScale3D(FMath::VInterpTo(GetActorScale3D(), attackScaleVec, FApp::GetDeltaTime(), 6.f));
		if (GetActorScale3D().Y > 0.51f) // if the monsters Y is this big then it has attacked the door
		{
			if (attacksDone < 6) //attacks done are less then 6 keep going
			{
				currentAttackCD = attackCD;
				doorHit = false;
				isAttackingDoor = false;
				attacksDone++;
			}
			// else that means the monster has broken the door set the target position to player and change the movement speed to attack one and set killing as true
			else
			{
				target = playerPos;
				currentSpeed = attackSpeed;
				isKilling = true;
			}
		}
	}
	else // else the scale him down
	{
		SetActorScale3D(FMath::VInterpTo(GetActorScale3D(), normalScaleVec, FApp::GetDeltaTime(), 6.f));
	}

	if (isKilling && distanceToPlayer < 1.f && target == playerPos) // if monster is is killing state and the distance is close then the player is set to dead
	{
		// player death
		playerComp->SetIsDead(true);
	}
}

//reset monster cool downs and make him hide
void ADoorMonsterAI::ResetMonster()
{
	target = hidePos;
	isAttackingDoor = false;
	currentEnableCD = coolDownEnable;
	currentAttackCD = attackCD;
	attacksDone = 0;
}

// Called every frame
void ADoorMonsterAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (gameState->GetIsPlaying())
	{
		ChaseTarget();
		DoorAttack();
		CoolDownCheck();
	}
}
