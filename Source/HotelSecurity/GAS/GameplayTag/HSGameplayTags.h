// Made by LSH

#pragma once

#include "GameplayTagContainer.h"

class HOTEL_SECURITY_API HSGameplayTags
{
public:
	static void InitGameplayTags();

	struct State
	{
		static FGameplayTag Idle;
		static FGameplayTag Move;
		static FGameplayTag Look;
		static FGameplayTag Run;
		static FGameplayTag FlashLock;
		static FGameplayTag Chased;
		static FGameplayTag HeartBeat;
		static FGameplayTag Feared;
		static FGameplayTag Fired;
		static FGameplayTag Die;
	};

	struct Action
	{
		static FGameplayTag Fearing;
		static FGameplayTag Flash;
		static FGameplayTag Interact;
		static FGameplayTag Zoom;
	};

	struct UI
	{
		struct PopUp
		{
			static FGameplayTag Report;
			static FGameplayTag Pause;
			static FGameplayTag Loading;
			static FGameplayTag GameClear;
			static FGameplayTag GameOver;
		};
		
		struct Action
		{
			static FGameplayTag ESC;
			static FGameplayTag Enter;
		};
	};

	struct Calculation
	{
		static FGameplayTag Speed;
		static FGameplayTag Fear;
		static FGameplayTag Battery;
	};

	struct GameplayCue
	{
		struct Camera
		{
			static FGameplayTag Shake_Default;
			static FGameplayTag Shake_HangingBody;
		};

		struct Sound
		{
			static FGameplayTag Flash;
			static FGameplayTag Chased;
			static FGameplayTag Die;
			static FGameplayTag Fearing;
		};
	};

	struct Cooldown
	{
		static FGameplayTag Interact;
	};
};