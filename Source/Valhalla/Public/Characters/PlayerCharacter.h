// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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

protected:
	virtual void BeginPlay() override;

private: // Private variables	
	/**
	* SpringArm:
	* 플레이어 캐릭터에 연결된 스프링 암 컴포넌트. 카메라와 캐릭터 간의 거리를 제어하는 역할을 함.
	* 카메라의 회전이나 거리 조정과 같은 다양한 카메라 관련 동작을 지원.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	/**
	* PlayerCamera:
	* 플레이어의 시점을 제어하는 카메라 컴포넌트. 스프링 암에 연결되어 있으며, 플레이어의 시점을 따라다니는 카메라.
	* Blueprint에서 읽기 전용(VisibleAnywhere)으로 설정되어 있으며, Private 접근 수준에서만 수정 가능.
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* PlayerCamera;
};
