// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"

void ABaseWeapon::Equip(USceneComponent* EquipTargetMesh, FName AttachSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(EquipTargetMesh, TransformRules, AttachSocketName);
}
