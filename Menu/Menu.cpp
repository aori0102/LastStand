#include <Menu.h>

#include <iostream>
#include <exception>

#include <GameCore.h>
#include <GameManager.h>
#include <KeyBindUIGroup.h>
#include <MediaManager.h>
#include <SliderUIGroup.h>
#include <Texture.h>

Menu* Menu::instance = nullptr;

void Menu::InitializeMenu() {

	// -------------
	// TITLE
	// -------------
	GameObject* title = GameObject::Instantiate("Menu Title", Layer::Menu);
	Image* title_image = title->AddComponent<Image>();
	title_image->showOnScreen = true;
	title_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Title), true);
	title->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::Title), title->transform->scale
	);
	title->Render = [this, title_image]() {
		if (IsActive())
			title_image->Render();
		};
	uiElementMap[UIElementIndex::Title] = title;

	// -------------
	// PLAY BUTTON
	// -------------
	GameObject* playButton = GameObject::Instantiate("Menu Play Button", Layer::Menu);
	Image* playButton_image = playButton->AddComponent<Image>();
	playButton_image->showOnScreen = true;
	playButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* playButton_button = playButton->AddComponent<Button>();
	playButton_button->backgroundColor = Color::TRANSPARENT;
	playButton_button->OnClick = [this]() {
		if (!IsActive())
			return false;
		std::cout << "Play Button Clicked!" << std::endl;
		GameManager::Instance()->SwitchScene(SceneIndex::Game);
		return true;
		};
	playButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::PlayButton), playButton->transform->position
	);
	playButton->Render = [this, playButton_image]() {
		if (IsActive())
			playButton_image->Render();
		};
	uiElementMap[UIElementIndex::PlayButton] = playButton;

	// -------------
	// PLAY LABEL
	// -------------
	GameObject* playButtonLabel = GameObject::Instantiate("Menu Play Button Label", Layer::Menu);
	Text* playButtonLabel_text = playButtonLabel->AddComponent<Text>();
	playButtonLabel_text->showOnScreen = true;
	playButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::PlayLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::PlayLabel)
	);
	playButtonLabel->transform->position = playButton->transform->position;
	playButtonLabel->Render = [this, playButtonLabel_text]() {
		if (IsActive())
			playButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::PlayLabel] = playButtonLabel;

	// -------------
	// SETTINGS BUTTON
	// -------------
	GameObject* settingsButton = GameObject::Instantiate("Menu Settings Button", Layer::Menu);
	Image* settingsButton_image = settingsButton->AddComponent<Image>();
	settingsButton_image->showOnScreen = true;
	settingsButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* settingsButton_button = settingsButton->AddComponent<Button>();
	settingsButton_button->backgroundColor = Color::TRANSPARENT;
	settingsButton_button->OnClick = [this]() {
		if (!IsActive())
			return false;
		std::cout << "Click Settings\n";
		SwitchMenu(MenuStateIndex::Settings);
		return true;
		};
	settingsButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::SettingsButton), settingsButton->transform->position
	);
	settingsButton->Render = [this, settingsButton_image]() {
		if (IsActive())
			settingsButton_image->Render();
		};
	uiElementMap[UIElementIndex::SettingsButton] = settingsButton;

	// -------------
	// SETTINGS LABEL
	// -------------
	GameObject* settingsButtonLabel = GameObject::Instantiate("Menu Settings Button Label", Layer::Menu);
	Text* settingsButtonLabel_text = settingsButtonLabel->AddComponent<Text>();
	settingsButtonLabel_text->showOnScreen = true;
	settingsButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::SettingsLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::SettingsLabel)
	);
	settingsButtonLabel->transform->position = settingsButton->transform->position;
	settingsButtonLabel->Render = [this, settingsButtonLabel_text]() {
		if (IsActive())
			settingsButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::SettingsLabel] = settingsButtonLabel;

	// -------------
	// QUIT BUTTON
	// -------------
	GameObject* quitButton = GameObject::Instantiate("Menu Quit Button", Layer::Menu);
	Image* quitButton_image = quitButton->AddComponent<Image>();
	quitButton_image->showOnScreen = true;
	quitButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* quitButton_button = quitButton->AddComponent<Button>();
	quitButton_button->backgroundColor = Color::TRANSPARENT;
	quitButton_button->OnClick = [this]() {
		if (!IsActive())
			return false;
		std::cout << "Quit Button Clicked!" << std::endl;
		return true;
		};
	quitButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::QuitButton), quitButton->transform->position
	);
	quitButton->Render = [this, quitButton_image]() {
		if (IsActive())
			quitButton_image->Render();
		};
	uiElementMap[UIElementIndex::QuitButton] = quitButton;

	// -------------
	// QUIT LABEL
	// -------------
	GameObject* quitButtonLabel = GameObject::Instantiate("Menu Quit Button Label", Layer::Menu);
	Text* quitButtonLabel_text = quitButtonLabel->AddComponent<Text>();
	quitButtonLabel_text->showOnScreen = true;
	quitButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::QuitLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::QuitLabel)
	);
	quitButtonLabel->transform->position = quitButton->transform->position;
	quitButtonLabel->Render = [this, quitButtonLabel_text]() {
		if (IsActive())
			quitButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::QuitLabel] = quitButtonLabel;

	// -------------
	// VERSION LABEL
	// -------------
	GameObject* versionLabel = GameObject::Instantiate("Menu Version Label", Layer::Menu);
	Text* versionLabel_text = versionLabel->AddComponent<Text>();
	versionLabel_text->showOnScreen = true;
	versionLabel_text->LoadText(
		GameCore::GetVersionString(), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::VersionLabel)
	);
	versionLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::VersionLabel), versionLabel->transform->scale
	);
	versionLabel->Render = [this, versionLabel_text]() {
		if (IsActive())
			versionLabel_text->Render();
		};
	uiElementMap[UIElementIndex::VersionLabel] = versionLabel;

	// -------------
	// MASTER VOLUME SLIDER
	// -------------
	SliderUIGroup* masterVolumeSlider = GameObject::Instantiate<SliderUIGroup>("Master Volume Slider", Layer::Menu);
	masterVolumeSlider->SetSliderLabel(UI_TEXT_MAP.at(UIElementIndex::MasterVolumeSlider));
	masterVolumeSlider->SetPosition(UI_POSITION_MAP.at(UIElementIndex::MasterVolumeSlider));
	masterVolumeSlider->OnValueUpdated = [](float value) {
		GameCore::SetMasterVolume(value);
		};
	uiElementMap[UIElementIndex::MasterVolumeSlider] = masterVolumeSlider;

	// -------------
	// SFX VOLUME SLIDER
	// -------------
	SliderUIGroup* sfxVolumeSlider = GameObject::Instantiate<SliderUIGroup>("SFX Volume Slider", Layer::Menu);
	sfxVolumeSlider->SetSliderLabel(UI_TEXT_MAP.at(UIElementIndex::SFXVolumeSlider));
	sfxVolumeSlider->SetPosition(UI_POSITION_MAP.at(UIElementIndex::SFXVolumeSlider));
	sfxVolumeSlider->OnValueUpdated = [](float value) {
		GameCore::SetSFXVolume(value);
		};
	uiElementMap[UIElementIndex::SFXVolumeSlider] = sfxVolumeSlider;

	// -------------
	// MASTER VOLUME SLIDER
	// -------------
	SliderUIGroup* musicVolumeSlider = GameObject::Instantiate<SliderUIGroup>("Master Volume Slider", Layer::Menu);
	musicVolumeSlider->SetSliderLabel(UI_TEXT_MAP.at(UIElementIndex::MusicVolumeSlider));
	musicVolumeSlider->SetPosition(UI_POSITION_MAP.at(UIElementIndex::MusicVolumeSlider));
	musicVolumeSlider->OnValueUpdated = [](float value) {
		GameCore::SetMusicVolume(value);
		};
	uiElementMap[UIElementIndex::MusicVolumeSlider] = musicVolumeSlider;

	// -------------
	// SETTINGS RETURN BUTTON
	// -------------
	GameObject* settingReturnButton = GameObject::Instantiate("Settings Return Button", Layer::Menu);
	Image* settingReturnButton_image = settingReturnButton->AddComponent<Image>();
	settingReturnButton_image->showOnScreen = true;
	settingReturnButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_ReturnButton), true);
	Button* settingReturnButton_button = settingReturnButton->AddComponent<Button>();
	settingReturnButton_button->backgroundColor = Color::TRANSPARENT;
	settingReturnButton_button->OnClick = [this]() {
		if (!IsActive())
			return false;
		std::cout << "Click Retrun\n";
		SwitchMenu(MenuStateIndex::MainMenu);
		return true;
		};
	settingReturnButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::SettingReturnButton), settingReturnButton->transform->scale
	);
	settingReturnButton->Render = [this, settingReturnButton_image]() {
		if (IsActive())
			settingReturnButton_image->Render();
		};
	uiElementMap[UIElementIndex::SettingReturnButton] = settingReturnButton;

	// -------------
	// SETTINGS RETURN LABEL
	// -------------
	GameObject* settingReturnLabel = GameObject::Instantiate("Settings Return Label", Layer::Menu);
	Text* settingReturnLabel_text = settingReturnLabel->AddComponent<Text>();
	settingReturnLabel_text->showOnScreen = true;
	settingReturnLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::SettingReturnLabel),
		Color::WHITE, 
		UI_FONT_SIZE_MAP.at(UIElementIndex::SettingReturnLabel)
	);
	settingReturnLabel->Render = [this, settingReturnLabel_text]() {
		if (IsActive())
			settingReturnLabel_text->Render();
		};
	settingReturnLabel->transform->position = settingReturnButton->transform->position;
	uiElementMap[UIElementIndex::SettingReturnLabel] = settingReturnLabel;

	// -------------
	// SETTINGS LABEL
	// -------------
	GameObject* settingTitleLabel = GameObject::Instantiate("Settings Title Label", Layer::Menu);
	Text* settingTitleLabel_text = settingTitleLabel->AddComponent<Text>();
	settingTitleLabel_text->showOnScreen = true;
	settingTitleLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::SettingsTitleLabel),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::SettingsTitleLabel)
	);
	settingTitleLabel->Render = [this, settingTitleLabel_text]() {
		if (IsActive())
			settingTitleLabel_text->Render();
		};
	settingTitleLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::SettingsTitleLabel), settingTitleLabel->transform->scale
	);
	uiElementMap[UIElementIndex::SettingsTitleLabel] = settingTitleLabel;

	// -------------
	// SETTINGS RETURN LABEL
	// -------------
	uiElementMap[UIElementIndex::KeyBindList] = GameObject::Instantiate<KeyBindUIGroup>("Key Bind UI Group", Layer::Menu);

}

void Menu::ShowCurrentMenu() {

	switch (currentMenuState) {

	case MenuStateIndex::MainMenu:

		uiElementMap.at(UIElementIndex::PlayButton)->Enable();
		uiElementMap.at(UIElementIndex::SettingsButton)->Enable();
		uiElementMap.at(UIElementIndex::QuitButton)->Enable();
		uiElementMap.at(UIElementIndex::PlayLabel)->Enable();
		uiElementMap.at(UIElementIndex::QuitLabel)->Enable();
		uiElementMap.at(UIElementIndex::SettingsLabel)->Enable();
		uiElementMap.at(UIElementIndex::Title)->Enable();
		uiElementMap.at(UIElementIndex::VersionLabel)->Enable();

		break;

	case MenuStateIndex::Settings:

		uiElementMap.at(UIElementIndex::MasterVolumeSlider)->Enable();
		uiElementMap.at(UIElementIndex::SFXVolumeSlider)->Enable();
		uiElementMap.at(UIElementIndex::MusicVolumeSlider)->Enable();
		uiElementMap.at(UIElementIndex::SettingReturnButton)->Enable();
		uiElementMap.at(UIElementIndex::SettingReturnLabel)->Enable();
		uiElementMap.at(UIElementIndex::KeyBindList)->Enable();
		uiElementMap.at(UIElementIndex::SettingsTitleLabel)->Enable();

		break;

	case MenuStateIndex::Saves:

		break;

	}

}

void Menu::HideCurrentMenu() {

	switch (currentMenuState) {

	case MenuStateIndex::MainMenu:

		uiElementMap.at(UIElementIndex::PlayButton)->Disable();
		uiElementMap.at(UIElementIndex::SettingsButton)->Disable();
		uiElementMap.at(UIElementIndex::QuitButton)->Disable();
		uiElementMap.at(UIElementIndex::PlayLabel)->Disable();
		uiElementMap.at(UIElementIndex::QuitLabel)->Disable();
		uiElementMap.at(UIElementIndex::SettingsLabel)->Disable();
		uiElementMap.at(UIElementIndex::Title)->Disable();
		uiElementMap.at(UIElementIndex::VersionLabel)->Disable();

		break;

	case MenuStateIndex::Settings:

		uiElementMap.at(UIElementIndex::MasterVolumeSlider)->Disable();
		uiElementMap.at(UIElementIndex::SFXVolumeSlider)->Disable();
		uiElementMap.at(UIElementIndex::MusicVolumeSlider)->Disable();
		uiElementMap.at(UIElementIndex::SettingReturnButton)->Disable();
		uiElementMap.at(UIElementIndex::SettingReturnLabel)->Disable();
		uiElementMap.at(UIElementIndex::KeyBindList)->Disable();
		uiElementMap.at(UIElementIndex::SettingsTitleLabel)->Disable();

		break;

	case MenuStateIndex::Saves:

		break;

	}

}

Menu::Menu() {

	if (instance)
		throw std::exception("Menu can only have one instance!");

	currentMenuState = MenuStateIndex::MainMenu;

	instance = this;

	InitializeMenu();

	OnEnabled = [this]() { ShowCurrentMenu(); };
	OnDisabled = [this]() { HideAll(); };

	HideAll();
	ShowCurrentMenu();

}

Menu::~Menu() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	instance = nullptr;

}

void Menu::SwitchMenu(MenuStateIndex targetMenu) {

	if (currentMenuState == targetMenu)
		return;

	HideCurrentMenu();

	currentMenuState = targetMenu;

	ShowCurrentMenu();

}

void Menu::HideAll() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

Menu* Menu::Instance() { return instance; }