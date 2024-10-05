#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unequip UMETA(DisplayName = "Unequip"),
	ECS_Equip UMETA(DisplayName = "Equip")
};