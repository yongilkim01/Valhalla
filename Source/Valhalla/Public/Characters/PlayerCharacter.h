// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class APlayerWeapon;
class UAnimMontage;
class UAnimInstance;

/**
* APlayerCharacter
* 플레이어 캐릭터를 정의하는 클래스. ABaseCharacter를 상속.
*/
UCLASS()
class VALHALLA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public: // Public methodes
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected: // Protected methodes
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	/**
	* 플레이어가 입력 액션 메소드.
	* @param Value: 이동 방향 및 크기를 나타내는 입력 값.
	*/
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interaction(const FInputActionValue& Value);
	void Equip(const FInputActionValue& Value);
	void LightAttack();
	void HeavyAttack();

private: // Private methodes
	/**
	* 애니메이션 관련 설정 초기화 메소드.
	* 1. AnimNotify 바인드.
	*/
	void InitAnimation();
	/** 장착 관련 애니메이션 몽타주 AnimNotify 초기화 메소드. */
	void InitEquipMontageNotify();
	void InitUnequipMontageNotify();
	/** EquipMontage 재생 중에 무기를 플레이어의 손에 부착하는 메소드. */
	void AttachWeaponToRightHand();
	void AttachWeaponToBack();

	/**
	* 애니메이션 몽타주 실행 메소드.
	*/
	void PlayLightAttackMontage();

private: // Private variables	
	/**
	* 플레이어 캐릭터에 연결된 스프링 암 컴포넌트. 카메라와 캐릭터 간의 거리를 제어하는 역할.
	* 카메라의 회전이나 거리 조정과 같은 다양한 카메라 관련 동작을 지원.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterData|Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	/**
	* 플레이어의 시점을 제어하는 카메라 컴포넌트. 스프링 암에 연결되어 있으며, 플레이어의 시점을 따라다니는 카메라.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "CharacterData|Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

protected: // Protected variables

	/**
	* 입력 맵핑을 관리하는 UInputMappingContext 객체. 입력 액션과 컨텍스트를 바인딩하여 플레이어가 입력을 통해 캐릭터를 제어.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputMappingContext* MappingContext = nullptr;

	/**
	* 플레이어 입력 액션.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* MoveInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* LookInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* InteractionInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* EquipInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* LightAttackInputAction = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData|Input")
	UInputAction* HeavyAttackInputAction = nullptr;

	/**
	* 플레이어의 애니메이션 몽타주.
	* 디폴트 값만 편집 가능(EditDefaultsOnly) 속성으로 설정.
	*/
	UPROPERTY(EditDefaultsOnly, Category = "CharacterData|Animation")
	UAnimMontage* EquipMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterData|Animation")
	UAnimMontage* UnequipMontage = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterData|Animation")
	UAnimMontage* LightAttackMontage = nullptr;

private: // Privated variables
	int32 CurrentComboCount = 0;
};
