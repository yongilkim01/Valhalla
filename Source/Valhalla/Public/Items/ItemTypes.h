#pragma once

UENUM(BlueprintType)
enum class EItemType : uint8
{
	EIT_None UMETA(DisplayName = "None"),
	EIT_Weapon UMETA(DisplayName = "Weapon")
};