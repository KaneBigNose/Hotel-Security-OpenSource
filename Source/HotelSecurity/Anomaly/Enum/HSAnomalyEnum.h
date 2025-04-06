// Made by LSH

#pragma once

UENUM(BlueprintType)
enum class EAnomalyType : uint8
{
	None UMETA(DisplayName = "None"),
	Location UMETA(DisplayName = "Location"),
	Rotation UMETA(DisplayName = "Rotation"),
	Scale UMETA(DisplayName = "Scale"),
	Disappear UMETA(DisplayName = "Disappear"),
	Change UMETA(DisplayName = "Change"),
	Fly UMETA(DisplayName = "Fly")
};