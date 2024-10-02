// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "BaseWeapon.generated.h"

class ABaseCharacter;
/**
 * 
 */
UCLASS()
class VALHALLA_API ABaseWeapon : public AItem
{
	GENERATED_BODY()

public: // 게터 세터
	ABaseCharacter* GetOwningCharacter();
	void SetOwningCharacter(ABaseCharacter* BaseCharacter);
	
private: // Private 변수
	// 현재 이 무기를 소유하고 있는 캐릭터 객체.
	UPROPERTY()
	ABaseCharacter* OwningCharacter = nullptr;
};
