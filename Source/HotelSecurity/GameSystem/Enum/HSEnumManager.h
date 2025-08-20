// Made by LSH

#pragma once

#include "CoreMinimal.h"

class HOTEL_SECURITY_API HSEnumManager
{
public:
	template <class EnumClass>
	static FName GetEnumAsFName(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		if (!EnumPtr)
		{
			return FName("Empty");
		}

		return FName(*EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString());
	}

	template <class EnumClass>
	static FString GetEnumAsFString(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		if (!EnumPtr)
		{
			return FString(TEXT("Empty"));
		}

		return *EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString();
	}
};