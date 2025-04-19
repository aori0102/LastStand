/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>
#include <Version.h>
class Menu : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {

		// Main Menu
		PlayButton,
		SettingsButton,
		QuitButton,
		PlayLabel,
		SettingsLabel,
		QuitLabel,
		Title,
		VersionLabel,
		TutorialButton,
		StatisticButton,

	};

	const std::unordered_map<UIElementIndex, std::string> UI_TEXT_MAP = {
		{ UIElementIndex::PlayLabel, "Play"},
		{ UIElementIndex::SettingsLabel, "Settings"},
		{ UIElementIndex::QuitLabel, "Quit"},
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::PlayButton, Vector2(138.0f, 284.0f) },
		{ UIElementIndex::SettingsButton, Vector2(138.0f, 411.0f) },
		{ UIElementIndex::QuitButton, Vector2(138.0f, 538.0f) },
		{ UIElementIndex::Title, Vector2(78.0f, 63.0f) },
		{ UIElementIndex::VersionLabel, Vector2(-5.0f, 0.0f) },
		{ UIElementIndex::TutorialButton, Vector2(419.0f, 432.0f) },
		{ UIElementIndex::StatisticButton, Vector2(419.0f, 304.0f) },
	};
	const std::unordered_map<UIElementIndex, int> UI_FONT_SIZE_MAP = {
		{ UIElementIndex::PlayLabel, 48 },
		{ UIElementIndex::SettingsLabel, 48 },
		{ UIElementIndex::QuitLabel, 48 },
		{ UIElementIndex::VersionLabel, 20 },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static Menu* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeMenu();
	void Show();
	void Hide();

public:

	Menu();
	~Menu();

	static Menu* Instance();

};