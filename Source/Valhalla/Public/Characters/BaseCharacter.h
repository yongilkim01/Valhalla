// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseWeapon;

UCLASS()
class VALHALLA_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	* 캐릭터에게 무기를 장착시키는 메소드
	*
	* @param Weapon: 캐릭터에게 장착시키려고 하는 무기 객체 포인터.
	*/
	virtual void EquipWeapon(ABaseWeapon* Weapon);
protected:
	virtual void BeginPlay() override;

public: // 게터 세터
	void SetCharacterWeapon(ABaseWeapon* Weapon);
	ABaseWeapon* GetChracterWeapon();

private: // Private 멤버 변수
	/**
	* 캐릭터가 가지고 있는 무기 객체.
	*/
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	ABaseWeapon* CharacterWeapon = nullptr;
};
