// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PlayerUnequipNotify.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE(FOnNotifiedSignature)

UCLASS()
class VALHALLA_API UPlayerUnequipNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	FOnNotifiedSignature OnNotified;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
