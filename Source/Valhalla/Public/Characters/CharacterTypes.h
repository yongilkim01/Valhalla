#pragma once

UENUM(BlueprintType)
enum class ECharacterEquipState : uint8
{
	ECS_Unequip UMETA(DisplayName = "Unequip"),
	ECS_Equip UMETA(DisplayName = "Equip")
};

UENUM(BlueprintType)
enum class ECharacterActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking")
};