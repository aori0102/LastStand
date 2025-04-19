/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>

class DeathMessage : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {
		Frame,
		WaveSurvivedLabel,
		ZombieKilledLabel,
		DamageDealtLabel,
		PointsLabel,
		WaveSurvivedValue,
		ZombieKilledValue,
		DamageDealtValue,
		PointsValue,
		MainMenuButton,
		MainMenuLabel,
		RetryButton,
		RetryLabel,
	};

	const int STAT_LABEL_FONT_SIZE = 20;
	const int BUTTON_LABEL_FONT_SIZE = 30;
	const float STAT_LABEL_OFFSET = 35.0f;
	const std::unordered_map<UIElementIndex, std::string> UI_LABEL_MAP = {
		{ UIElementIndex::DamageDealtLabel, "Damage Dealt:" },
		{ UIElementIndex::WaveSurvivedLabel, "Wave Survived:" },
		{ UIElementIndex::PointsLabel, "Points:" },
		{ UIElementIndex::ZombieKilledLabel, "Zombie Killed:" },
		{ UIElementIndex::RetryLabel, "Retry" },
		{ UIElementIndex::MainMenuLabel, "Main Menu" },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::Frame, Vector2(290.0f, 172.0f) },
		{ UIElementIndex::MainMenuButton, Vector2(391.0f, 459.0f) },
		{ UIElementIndex::RetryButton, Vector2(664.0f, 459.0f) },
		{ UIElementIndex::WaveSurvivedValue, Vector2(670.0f, 294.0f) },
		{ UIElementIndex::ZombieKilledValue, Vector2(670.0f, 330.0f) },
		{ UIElementIndex::DamageDealtValue, Vector2(670.0f, 366.0f) },
		{ UIElementIndex::PointsValue, Vector2(670.0f, 402.0f) },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;
	
	static DeathMessage* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	DeathMessage();
	~DeathMessage();
	void UpdateMessage();

	static DeathMessage* Instance();

};