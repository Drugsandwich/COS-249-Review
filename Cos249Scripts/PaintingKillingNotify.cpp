// Fill out your copyright notice in the Description page of Project Settings.

#include "PaintingKillingNotify.h"

//Function that is used to notify the painting monster script that is killing the player this is used for animation event
void UPaintingKillingNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    //death to player
    monsterLogic = Cast<AMonsterPaintingLogic>(MeshComp->GetOwner());

    if (monsterLogic != nullptr)
    {
        monsterLogic->AnimEventKill();
    }
}