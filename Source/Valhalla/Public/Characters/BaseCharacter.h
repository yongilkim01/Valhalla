// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "BaseCharacter.generated.h"

class ABaseWeapon;
class AItem;

UCLASS()
class VALHALLA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

public: // 게터 세터
	FORCEINLINE void SetCharacterWeapon(AItem* Weapon) { CharacterWeapon = Weapon; }
	FORCEINLINE AItem* GetCharacterWeapon() { return CharacterWeapon; }

	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE AItem* GetOverlappingItem() { return OverlappingItem; }

	FORCEINLINE void SetCharacterEquipState(ECharacterEquipState State) { CharacterEquipState = State; }
	FORCEINLINE ECharacterEquipState GetCharacterEquipState() { return CharacterEquipState; }

	FORCEINLINE void SetCharacterActionState(ECharacterActionState State) { CharacterActionState = State; }
	FORCEINLINE ECharacterActionState GetCharacterActionState() { return CharacterActionState; }

private: // Private 멤버 변수
	/**
	* 플레이어 범위 안에 들어온 아이템 객체
	*/
	UPROPERTY(VisibleAnywhere, Category = "CharacterData|Item")
	AItem* OverlappingItem = nullptr;
	/**
	* 캐릭터가 가지고 있는 무기 객체.
	*/
	UPROPERTY(VisibleAnywhere, Category = "CharacterData|Item")
	AItem* CharacterWeapon = nullptr;

	/** 현재 플레이어 캐릭터의 장착 상태를 나타내는 멤버 변수. */
	ECharacterEquipState CharacterEquipState = ECharacterEquipState::ECS_Unequip;

	/** 현재 플레이어의 액션 상태를 나타내는 멤버 변수. */
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterActionState CharacterActionState = ECharacterActionState::EAS_Unoccupied;
};
