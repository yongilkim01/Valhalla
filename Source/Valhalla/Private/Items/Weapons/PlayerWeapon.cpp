// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/PlayerWeapon.h"
#include "Components/SphereComponent.h"

#include "ValhallaDebugHelper.h"

APlayerWeapon::APlayerWeapon()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ShpereCollision"));
	SphereCollision->SetupAttachment(GetRootComponent());
}

void APlayerWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon::OnSphereOverlap);
	SphereCollision->OnComponentEndOverlap.AddDynamic(this, &APlayerWeapon::OnSphereEndOverlap);

}

void APlayerWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString OtherActorName = OtherActor->GetName();
	Debug::Print(OtherActorName, FColor::Red);
}

void APlayerWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString OtherActorName = FString("Ending Overlap with: ") + OtherActor->GetName();
	Debug::Print(OtherActorName, FColor::Green);
}
