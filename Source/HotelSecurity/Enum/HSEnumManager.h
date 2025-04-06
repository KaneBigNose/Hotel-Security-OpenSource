// Made by LSH

#pragma once

#include "CoreMinimal.h"

template <class EnumClass>
class HOTEL_SECURITY_API HSEnumManager
{
public:
	static FName GetEnumAsFName(EnumClass EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EnumClass>();

		if (!EnumPtr)
		{
			return FName("Empty");
		}

		return FName(*EnumPtr->GetDisplayNameTextByValue(static_cast<int64>(EnumValue)).ToString());
	}
};