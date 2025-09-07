// Made by LSH

#include "GAS/GameplayTag/HSGameplayTags.h"

FGameplayTag HSGameplayTags::State::Idle;
FGameplayTag HSGameplayTags::State::Move;
FGameplayTag HSGameplayTags::State::Look;
FGameplayTag HSGameplayTags::State::Run;
FGameplayTag HSGameplayTags::State::FlashLock;
FGameplayTag HSGameplayTags::State::Chased;
FGameplayTag HSGameplayTags::State::HeartBeat;
FGameplayTag HSGameplayTags::State::Feared;
FGameplayTag HSGameplayTags::State::Fired;
FGameplayTag HSGameplayTags::State::Die;

FGameplayTag HSGameplayTags::Action::Fearing;
FGameplayTag HSGameplayTags::Action::Flash;
FGameplayTag HSGameplayTags::Action::Interact;
FGameplayTag HSGameplayTags::Action::Zoom;

FGameplayTag HSGameplayTags::UI::PopUp::Report;
FGameplayTag HSGameplayTags::UI::PopUp::Pause;
FGameplayTag HSGameplayTags::UI::PopUp::Loading;
FGameplayTag HSGameplayTags::UI::PopUp::GameClear;
FGameplayTag HSGameplayTags::UI::PopUp::GameOver;

FGameplayTag HSGameplayTags::UI::Action::ESC;
FGameplayTag HSGameplayTags::UI::Action::Enter;

FGameplayTag HSGameplayTags::Calculation::Speed;
FGameplayTag HSGameplayTags::Calculation::Fear;
FGameplayTag HSGameplayTags::Calculation::Battery;

FGameplayTag HSGameplayTags::GameplayCue::Camera::Shake_Default;
FGameplayTag HSGameplayTags::GameplayCue::Camera::Shake_HangingBody;

FGameplayTag HSGameplayTags::GameplayCue::Sound::Flash;
FGameplayTag HSGameplayTags::GameplayCue::Sound::Chased;
FGameplayTag HSGameplayTags::GameplayCue::Sound::Die;
FGameplayTag HSGameplayTags::GameplayCue::Sound::Fearing;

FGameplayTag HSGameplayTags::Cooldown::Interact;

void HSGameplayTags::InitGameplayTags()
{
	if (State::Idle.IsValid())
	{
		return;
	}

	State::Idle = FGameplayTag::RequestGameplayTag(FName("Character.State.Idle"));
	State::Move = FGameplayTag::RequestGameplayTag(FName("Character.State.Move"));
	State::Look = FGameplayTag::RequestGameplayTag(FName("Character.State.Look"));
	State::Run = FGameplayTag::RequestGameplayTag(FName("Character.State.Run"));
	State::FlashLock = FGameplayTag::RequestGameplayTag(FName("Character.State.FlashLock"));
	State::Chased = FGameplayTag::RequestGameplayTag(FName("Character.State.Chased"));
	State::HeartBeat = FGameplayTag::RequestGameplayTag(FName("Character.State.HeartBeat"));
	State::Feared = FGameplayTag::RequestGameplayTag(FName("Character.State.Feared"));
	State::Fired = FGameplayTag::RequestGameplayTag(FName("Character.State.Fired"));
	State::Die = FGameplayTag::RequestGameplayTag(FName("Character.State.Die"));

	Action::Fearing = FGameplayTag::RequestGameplayTag(FName("Character.Action.Fearing"));
	Action::Flash = FGameplayTag::RequestGameplayTag(FName("Character.Action.Flash"));
	Action::Interact = FGameplayTag::RequestGameplayTag(FName("Character.Action.Interact"));
	Action::Zoom = FGameplayTag::RequestGameplayTag(FName("Character.Action.Zoom"));

	UI::PopUp::Report = FGameplayTag::RequestGameplayTag(FName("Character.UI.PopUp.Report"));
	UI::PopUp::Pause = FGameplayTag::RequestGameplayTag(FName("Character.UI.PopUp.Pause"));
	UI::PopUp::Loading = FGameplayTag::RequestGameplayTag(FName("Character.UI.PopUp.Loading"));
	UI::PopUp::GameClear = FGameplayTag::RequestGameplayTag(FName("Character.UI.PopUp.GameClear"));
	UI::PopUp::GameOver = FGameplayTag::RequestGameplayTag(FName("Character.UI.PopUp.GameOver"));

	UI::Action::ESC = FGameplayTag::RequestGameplayTag(FName("Character.UI.Action.ESC"));
	UI::Action::Enter = FGameplayTag::RequestGameplayTag(FName("Character.UI.Action.Enter"));

	Calculation::Speed = FGameplayTag::RequestGameplayTag(FName("Character.Calculation.Speed"));
	Calculation::Fear = FGameplayTag::RequestGameplayTag(FName("Character.Calculation.Fear"));
	Calculation::Battery = FGameplayTag::RequestGameplayTag(FName("Character.Calculation.Battery"));

	GameplayCue::Camera::Shake_Default = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Camera.Shake.Default"));
	GameplayCue::Camera::Shake_HangingBody = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Camera.Shake.HangingBody"));

	GameplayCue::Sound::Flash = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Sound.Flash"));
	GameplayCue::Sound::Chased = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Sound.Chased"));
	GameplayCue::Sound::Die = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Sound.Die"));
	GameplayCue::Sound::Fearing = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Sound.Fearing"));

	Cooldown::Interact = FGameplayTag::RequestGameplayTag(FName("Character.Cooldown.Interact"));
}