// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterPaintingLogic.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PaintingKillingNotify.generated.h"

/**
 * 
 */
UCLASS()
class COSROOM_API UPaintingKillingNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

private:
	AMonsterPaintingLogic *monsterLogic;
};
