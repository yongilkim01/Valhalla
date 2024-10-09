// Fill out your copyright notice in the Description page of Project Settings.

#include "Items/Item.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{
	// 프레임마다 Tick 하지 않도록 설정.
	PrimaryActorTick.bCanEverTick = false;

	// 아이템 메쉬를 루트 컴포넌트로 설정.
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	SetRootComponent(ItemMesh);

	// 아이템 콜리전 박스를 루트 컴포넌트에 부착.
	ItemCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCollisionBox"));
	ItemCollisionBox->SetupAttachment(GetRootComponent());
	ItemCollisionBox->SetBoxExtent(FVector(20.f));
	ItemCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereCollision"));
	//SphereCollision->SetupAttachment(GetRootComponent());
}

//void AItem::BeginPlay()
//{
//	Super::BeginPlay();
//
//	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
//	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
//}
//
//void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	const FString OtherActorName = OtherActor->GetName();
//	Debug::Print(OtherActorName, FColor::Red);
//}
//
//void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	const FString OtherActorName = FString("Ending Overlap with: ") + OtherActor->GetName();
//	Debug::Print(OtherActorName, FColor::Green);
//}