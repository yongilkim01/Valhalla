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

/**
* APlayerCharacter
* 플레이어 캐릭터를 정의하는 클래스. ABaseCharacter를 상속.
*/
UCLASS()
class VALHALLA_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	* 캐릭터에게 무기를 장착시키는 메소드
	*
	* @param Weapon: 캐릭터에게 장착시키려고 하는 무기 객체 포인터.
	*/
	virtual void EquipWeapon(ABaseWeapon* Weapon) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);

	/**
	* 플레이어가 이동할 때 호출되는 메소드로, FInputActionValue 타입의 입력 값을 받아 처리.
	* @param Value: 이동 방향 및 크기를 나타내는 입력 값.
	*/
	void Move(const FInputActionValue& Value);
	/**
	* 마우스가 움직일 때 호출되는 메소드로, FInputActionValue 타입의 입력 값을 받아 처리.
	* @param Value: 마우스의 이동 방향 및 크기를 나타내는 입력 값.
	*/
	void Look(const FInputActionValue& Value);
	/**
	* 아이템을
	* @param Value: 마우스의 이동 방향 및 크기를 나타내는 입력 값.
	*/
	void Interaction(const FInputActionValue& Value);

private: // Private variables	
	/**
	* 플레이어 캐릭터에 연결된 스프링 암 컴포넌트. 카메라와 캐릭터 간의 거리를 제어하는 역할.
	* 카메라의 회전이나 거리 조정과 같은 다양한 카메라 관련 동작을 지원.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm = nullptr;

	/**
	* 플레이어의 시점을 제어하는 카메라 컴포넌트. 스프링 암에 연결되어 있으며, 플레이어의 시점을 따라다니는 카메라.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera = nullptr;

protected: // Protected variables
	/**
	* 입력 맵핑을 관리하는 UInputMappingContext 객체. 입력 액션과 컨텍스트를 바인딩하여 플레이어가 입력을 통해 캐릭터를 제어.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* MappingContext = nullptr;
	/**
	* 플레이어 캐릭터의 이동을 처리하는 입력 액션.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveInputAction = nullptr;
	/**
	* 플레이어 카메라의 회전을 마우스의 이동을 따라서 처리하는 입력 액션.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookInputAction = nullptr;
	/**
	* 플레이어가 상호작용하는 액션.
	* Blueprint에서 편집 가능(EditAnywhere)하며, Blueprint에서 읽기 전용(BlueprintReadOnly) 속성으로 설정.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractionInputAction = nullptr;
};
