// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animations/AnimInstances/BaseAnimInstance.h"
#include "Characters/CharacterTypes.h"
#include "CharacterAnimInstance.generated.h"

/**
 * 캐릭터들의 애님 인스턴스 C++ 클래스
 * BaseCharacter들의 애니매이션을 담당.
 */
UCLASS()
class VALHALLA_API UCharacterAnimInstance : public UBaseAnimInstance
{
	GENERATED_BODY()

public:
	/**
	* 애니메이션 인스턴스가 생성되고 초기화 될 때 호출.
	* 캐릭터 레퍼런스를 가져와서 할당.
	*/
	virtual void NativeInitializeAnimation() override;
	/**
	* 애니메이션 업데이트를 수행하는 매소드.
	* 애니메이션 상태나 캐릭터 상태를 업데이트하는데 사용.
	* 
	* @param DeltaSeconds: 마지막 프레임에서 현재 프레임까지의 경과 시간.
	*/
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds);

protected:
	// 현재 이 애니메이션 인스턴스를 소유하고 있는 캐릭터 객체.
	UPROPERTY()
	class ABaseCharacter* OwningCharacter = nullptr;
	
	// OwingCharacter의 CharacterMovementComponent 객체.
	UPROPERTY()
	class UCharacterMovementComponent* OwningMovementComponent = nullptr;

	// 애니메이션 상태를 변경시키기 위한 캐릭터 객체의 움직이는 속도.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed = 0.f;

	// 애니메이션 상태를 변경시키기 위한 캐릭터의 움직임 유무.
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool IsAcceleration = false;

	ECharacterState CharacterState;
	
};