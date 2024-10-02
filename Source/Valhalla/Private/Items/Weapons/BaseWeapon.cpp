// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/BaseWeapon.h"
#include "Characters/BaseCharacter.h"

ABaseCharacter* ABaseWeapon::GetOwningCharacter()
{
    if (OwningCharacter) return OwningCharacter;
    else return nullptr;
}

void ABaseWeapon::SetOwningCharacter(ABaseCharacter* BaseCharacter)
{
    OwningCharacter = BaseCharacter;
}
