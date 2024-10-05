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

	/**
	* 캐릭터에게 무기를 할당시키는 메소드.
	*
	* @param Weapon: 캐릭터에게 장착시키려고 하는 무기 객체 포인터.
	*/
	virtual void EquipWeapon(ABaseWeapon* Weapon);

	/**
	* 캐릭터 액터에게 또 다른 액터를 부착시키는 메소드.
	* 
	* @param AttachItem: 캐릭터 액터에게 부착시키려고 하는 액터 객체.
	*/
	void AttachActorToCharacter(AItem* AttachItem);

protected:
	virtual void BeginPlay() override;

public: // 게터 세터
	FORCEINLINE void SetCharacterWeapon(ABaseWeapon* Weapon) { CharacterWeapon = Weapon; }
	FORCEINLINE ABaseWeapon* GetChracterWeapon() { return CharacterWeapon; }

	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE AItem* GetOverlappingItem() { return OverlappingItem; }

	FORCEINLINE void SetCharacterState(ECharacterState State) { CharacterState = State; }
	FORCEINLINE ECharacterState GetCharacterState() { return CharacterState; }

private: // Private 멤버 변수
	/**
	* 플레이어 범위 안에 들어온 아이템 객체
	*/
	UPROPERTY(VisibleAnywhere, Category = "Item")
	AItem* OverlappingItem = nullptr;
	/**
	* 캐릭터가 가지고 있는 무기 객체.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Item|Weapon")
	ABaseWeapon* CharacterWeapon = nullptr;

	/** 현재 플레이어 캐릭터의 상태를 담고 있는 변수. */
	ECharacterState CharacterState = ECharacterState::ECS_Unequip;
};
