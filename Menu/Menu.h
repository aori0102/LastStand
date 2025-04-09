#pragma once

#include <unordered_map>

#include <GameObject.h>
#include <Utils.h>
#include <Version.h>

enum class MenuStateIndex {

	MainMenu,
	Settings,
	Saves,

};

class Menu : public GameObject {

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

		// Settings
		MasterVolumeSlider,
		SFXVolumeSlider,
		MusicVolumeSlider,
		SettingReturnButton,
		SettingReturnLabel,
		KeyBindList,
		SettingsTitleLabel,

	};

	const std::unordered_map<UIElementIndex, std::string> UI_TEXT_MAP = {
		{ UIElementIndex::PlayLabel, "Play"},
		{ UIElementIndex::SettingsLabel, "Settings"},
		{ UIElementIndex::QuitLabel, "Quit"},
		{ UIElementIndex::MasterVolumeSlider, "Master Volume"},
		{ UIElementIndex::SFXVolumeSlider, "SFX Volume"},
		{ UIElementIndex::MusicVolumeSlider, "Music Volume"},
		{ UIElementIndex::SettingReturnLabel, "Return"},
		{ UIElementIndex::SettingsTitleLabel, "Settings"},
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::PlayButton, Vector2(138.0f, 284.0f) },
		{ UIElementIndex::SettingsButton, Vector2(138.0f, 411.0f) },
		{ UIElementIndex::QuitButton, Vector2(138.0f, 538.0f) },
		{ UIElementIndex::Title, Vector2(78.0f, 63.0f) },
		{ UIElementIndex::VersionLabel, Vector2(1162.0f, 692.0f) },
		{ UIElementIndex::MasterVolumeSlider, Vector2(301.0f, 174.0f) },
		{ UIElementIndex::SFXVolumeSlider, Vector2(301.0f, 221.0f) },
		{ UIElementIndex::MusicVolumeSlider, Vector2(301.0f, 268.0f) },
		{ UIElementIndex::SettingReturnButton, Vector2(540.0f, 654.0f) },
		{ UIElementIndex::SettingsTitleLabel, Vector2(546.0f, 33.0f) },
	};
	const std::unordered_map<UIElementIndex, int> UI_FONT_SIZE_MAP = {
		{ UIElementIndex::PlayLabel, 48 },
		{ UIElementIndex::SettingsLabel, 48 },
		{ UIElementIndex::QuitLabel, 48 },
		{ UIElementIndex::SettingReturnLabel, 24 },
		{ UIElementIndex::VersionLabel, 20 },
		{ UIElementIndex::SettingsTitleLabel, 48 },
	};

private:

	MenuStateIndex currentMenuState;
	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;

	static Menu* instance;

private:

	void InitializeMenu();
	void HideCurrentMenu();
	void ShowCurrentMenu();

public:

	Menu();
	~Menu();
	void SwitchMenu(MenuStateIndex targetMenu);
	void HideAll();

	static Menu* Instance();

};