// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "ValhallaDebugHelper.h"

/**
* APlayerCharacter 생성자:
* 캐릭터의 기본 구성 요소 및 초기값을 설정하는 생성자.
* 캡슐 컴포넌트, 스프링 암, 카메라 컴포넌트와 캐릭터 이동 설정을 초기화함.
*/
APlayerCharacter::APlayerCharacter()
{
	// 캡슐 컴포넌트 크기 설정 (폭 42, 높이 96)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	// 캐릭터가 회전할 때 컨트롤러의 회전을 사용하지 않도록 설정 (피치, 요, 롤)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 스프링 암 컴포넌트 생성 및 초기화 (캐릭터의 루트 컴포넌트에 부착)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 200.f; // 스프링 암 길이 설정
	SpringArm->SocketOffset = FVector(0.f, 55.f, 65.f); // 카메라의 소켓 오프셋 설정
	SpringArm->bUsePawnControlRotation = true; // 컨트롤러 회전을 스프링 암에 반영

	// 카메라 컴포넌트 생성 및 스프링 암에 부착
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // 스프링 암의 소켓에 카메라 부착
	PlayerCamera->bUsePawnControlRotation = false; // 카메라는 자체 회전을 사용하지 않음

	// 캐릭터 이동 관련 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 이동 방향에 따라 회전하도록 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // 캐릭터 회전 속도 설정 (Yaw 축)
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 캐릭터의 최대 걷기 속도 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 걷기 중 제동력 설정
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Debug::Print(TEXT("Working"));
}
