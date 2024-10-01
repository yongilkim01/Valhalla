// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/CharacterAnimInstance.h"
#include "Characters/BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// 애니메이션 인스턴스 초기화
void UCharacterAnimInstance::NativeInitializeAnimation()
{
	// 현재 가지고 있는 폰 객체를 ABaseCharacter 객체로 형변환후 할당.
	OwningCharacter = Cast<ABaseCharacter>(TryGetPawnOwner());

	// 소유 캐릭터 객체 할당 성공시 캐릭터 무브먼트 객체 할당.
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	// 소유 캐릭터 객체와 캐릭터 무브먼트 객체 중 하나라도 nullptr일 경우 return.
	if (!OwningCharacter || !OwningMovementComponent) return;

	// 소유 캐릭터 객체의 물리 속도를 GroundSpeed의 할당.
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// 캐릭터 무브먼트의 가속도 값이 0 이상일 경우 움직이고 있다고 판단.
	IsAcceleration =  OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
