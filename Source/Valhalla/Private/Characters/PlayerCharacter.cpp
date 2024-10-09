// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PlayerCharacter.h"
#include "Items/Weapons/PlayerWeapon.h"
#include "Animations/AnimNotifies/PlayerEquipNotify.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // 스프링 암의 소켓에 카메라 부착
	Camera->bUsePawnControlRotation = false; // 카메라는 자체 회전을 사용하지 않음

	// 캐릭터 이동 관련 설정
	GetCharacterMovement()->bOrientRotationToMovement = true; // 캐릭터가 이동 방향에 따라 회전하도록 설정
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // 캐릭터 회전 속도 설정 (Yaw 축)
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 캐릭터의 최대 걷기 속도 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 걷기 중 제동력 설정
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// APlayerController 타입의 컨트롤러를 캐스팅하여 플레이어의 컨트롤러인지 확인
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		// UEnhancedInputLocalPlayerSubsystem을 가져옴, 입력 서브시스템에 액세스
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// 입력 맵핑 컨텍스트를 서브시스템에 추가, 우선순위 0으로 설정
			SubSystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	// 애니메이션 관련 설정 초기화.
	InitAnimation();
}

void APlayerCharacter::InitAnimation()
{
	// Equip Montage 초기화.
	InitEquipMontageNotify();
}


void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::MoveForward(float Value)
{
	// 컨트롤러가 유효하고, Value가 0이 아닌 경우에만 처리
	if (Controller && (Value != 0.f))
	{
		// 캐릭터의 전방 벡터(FVector)를 가져옴
		FVector Forward = GetActorForwardVector();
		// 입력된 Value 값을 기준으로 전방 방향으로 캐릭터 이동
		AddMovementInput(Forward, Value);
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	// InputAction(IA_Move)의 값 타입이 Axis2D일 경우 FVector2D로 형변환
	const FVector2D MovementVector = Value.Get<FVector2D>();

	// 현재 회전값으로 값을 초기화
	const FRotator MovementRotation(0.f, GetController()->GetControlRotation().Yaw, 0.f);

	// 앞으로 이동을 했을 경우
	if (MovementVector.Y != 0.f)
	{
		// 회전값을 설정
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	// 옆으로 이동을 했을 경우
	if (MovementVector.X != 0.f)
	{
		// 회전값을 설정
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	// InputAction(IA_Look)의 값 타입이 Axis2D일 경우 FVector2D로 형변환
	const FVector2D LookVector = Value.Get<FVector2D>();

	// 입력으로 들어온 값, 즉 마우스의 위치 값의 가로 이동값이 0이 아닐 경우
	if (LookVector.X != 0.f)
	{
		AddControllerYawInput(LookVector.X);
	}
	// 입력으로 들어온 값, 즉 마우스의 위치 값의 세로 이동값이 0이 아닐 경우
	if(LookVector.Y != 0.f)
	{
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::Interaction(const FInputActionValue& Value)
{
	// 현재 범위 안에 들어온 아이템이 있다면
	if (GetOverlappingItem())
	{
		// 캐릭터에게 아이템을 부착
		GetOverlappingItem()->AttachItem(GetMesh(), FName("BackWeaponSocket"));
		SetCharacterWeapon(GetOverlappingItem());
	}
}

void APlayerCharacter::Equip(const FInputActionValue& Value)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
	}
}

void APlayerCharacter::InitEquipMontageNotify()
{
	// EquipMontage이 유효한지 검사.
	if (EquipMontage)
	{
		// EquipMontage에 있는 Notify들을 가져옴.
		const TArray<FAnimNotifyEvent> EventNotifies = EquipMontage->Notifies;

		// Notify의 수 만큼 반복.
		for (FAnimNotifyEvent EventNotify : EventNotifies)
		{
			// PlayerEquipNotify로 캐스팅이 가능한지 검사.
			if (UPlayerEquipNotify* EquipNotify = Cast<UPlayerEquipNotify>(EventNotify.Notify))
			{
				// 캐스팅이 완료됬다면 해당 Notify에서 실행할 메소드를 바인딩.
				EquipNotify->OnNotified.AddUObject(this, &APlayerCharacter::AttachWeaponToRightHand);
			}
		}

	}
}

void APlayerCharacter::AttachWeaponToRightHand()
{
	Debug::Print(TEXT("내 손안에 무기 생성"));
	// 캐릭터에게 아이템을 부착
	if (GetOverlappingItem())
	{
		// 캐릭터의 상태를 장착 상태로 변경
		SetCharacterState(ECharacterState::ECS_Equip);
		GetOverlappingItem()->AttachItem(GetMesh(), FName("RightHandWeaponSocket"));
		//GetMesh()->LinkAnimClassLayers(GetOverlappingItem());
	}
}


void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// UInputComponent가 UEnhancedInputComponent로 캐스팅 가능한지 확인
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// MoveAction을 입력에 바인딩, Triggered 이벤트가 발생할 때 Move 함수 호출
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(InteractionInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interaction);
		EnhancedInputComponent->BindAction(EquipInputAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Equip);
	}

	// 축 입력 방식으로 캐릭터를 전방으로 이동시키는 코드를 주석 처리
	// PlayerInputComponent->BindAxis(FName("MoveForward"), this, &APlayerCharacter::MoveForward);
}