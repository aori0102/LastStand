#pragma once

#include <string>
#include <unordered_map>

#include <GameObject.h>

class PauseMenu : public GameObject {

private:

	enum class UIElementIndex {
		Title,
		Frame,
		ResumeButton,
		ResumeLabel,
		SettingsButton,
		SettingsLabel,
		MainMenuButton,
		MainMenuLabel,
	};
	
	const int TITLE_FONT_SIZE = 40;
	const int BUTTON_LABEL_FONT_SIZE = 30;
	const std::unordered_map<UIElementIndex, std::string> UI_LABEL_MAP = {
		{ UIElementIndex::Title, "Paused" },
		{ UIElementIndex::ResumeLabel, "Resume" },
		{ UIElementIndex::SettingsLabel, "Settings" },
		{ UIElementIndex::MainMenuLabel, "MainMenu" },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_POSITION_MAP = {
		{ UIElementIndex::Title, Vector2(0.0f, -11.0f) },
		{ UIElementIndex::Frame, Vector2(475.0f, 169.0f) },
		{ UIElementIndex::ResumeButton, Vector2(521.0f, 244.0f) },
		{ UIElementIndex::SettingsButton, Vector2(521.0f, 335.0f) },
		{ UIElementIndex::MainMenuButton, Vector2(521.0f, 426.0f) },
	};

private:

	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;
	static PauseMenu* instance;

private:

	void InitializeUI();
	void Show();
	void Hide();

public:

	PauseMenu();
	~PauseMenu();
	static PauseMenu* Instance();

};