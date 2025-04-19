/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>

class SettingsUI : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class UIElementIndex {
		MasterVolumeSlider,
		SFXVolumeSlider,
		MusicVolumeSlider,
		Title,
		ReturnButton,
		ReturnLabel,
		KeyBindList,
	};

	const std::unordered_map<UIElementIndex, std::string> UI_TEXT_MAP = {
		{ UIElementIndex::MasterVolumeSlider, "Master Volume"},
		{ UIElementIndex::SFXVolumeSlider, "SFX Volume"},
		{ UIElementIndex::MusicVolumeSlider, "Music Volume"},
		{ UIElementIndex::ReturnLabel, "Return"},
		{ UIElementIndex::Title, "Settings"},
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::MasterVolumeSlider, Vector2(301.0f, 174.0f) },
		{ UIElementIndex::SFXVolumeSlider, Vector2(301.0f, 221.0f) },
		{ UIElementIndex::MusicVolumeSlider, Vector2(301.0f, 268.0f) },
		{ UIElementIndex::ReturnButton, Vector2(540.0f, 654.0f) },
		{ UIElementIndex::Title, Vector2(546.0f, 33.0f) },
	};
	const std::unordered_map<UIElementIndex, int> UI_FONT_SIZE_MAP = {
		{ UIElementIndex::ReturnLabel, 24 },
		{ UIElementIndex::Title, 48 },
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static SettingsUI* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	SettingsUI();
	~SettingsUI();
	void UpdateConfig();

	static SettingsUI* Instance();

};