#include <SettingsUI.h>

#include <GameCore.h>
#include <GameManager.h>
#include <KeyBindUIGroup.h>
#include <MediaManager.h>
#include <SliderUIGroup.h>
#include <Texture.h>

void SettingsUI::InitializeUI() {

	// -------------
	// MASTER VOLUME SLIDER
	// -------------
	SliderUIGroup* masterVolumeSlider = GameObject::Instantiate<SliderUIGroup>("Master Volume Slider", Layer::Menu);
	masterVolumeSlider->SetSliderLabel(UI_TEXT_MAP.at(UIElementIndex::MasterVolumeSlider));
	masterVolumeSlider->SetPosition(UI_POSITION_MAP.at(UIElementIndex::MasterVolumeSlider));
	masterVolumeSlider->OnValueUpdated = [](float value) {
		GameCore::SetMasterVolume(value);
		};
	masterVolumeSlider->SetValue(GameCore::GetMasterVolume());
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
	sfxVolumeSlider->SetValue(GameCore::GetSFXVolume());
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
	musicVolumeSlider->SetValue(GameCore::GetMusicVolume());
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
	settingReturnButton_button->OnClick = []() {
		GameManager::Instance()->SwitchToPreviousScene();
		return true;
		};
	settingReturnButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::ReturnButton), settingReturnButton->transform->scale
	);
	settingReturnButton->Render = [settingReturnButton_image]() {
		settingReturnButton_image->Render();
		};
	uiElementMap[UIElementIndex::ReturnButton] = settingReturnButton;

	// -------------
	// SETTINGS RETURN LABEL
	// -------------
	GameObject* settingReturnLabel = GameObject::Instantiate("Settings Return Label", Layer::Menu);
	Text* settingReturnLabel_text = settingReturnLabel->AddComponent<Text>();
	settingReturnLabel_text->showOnScreen = true;
	settingReturnLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::ReturnLabel),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::ReturnLabel)
	);
	settingReturnLabel->Render = [settingReturnLabel_text]() {
		settingReturnLabel_text->Render();
		};
	settingReturnLabel->transform->position = settingReturnButton->transform->position;
	uiElementMap[UIElementIndex::ReturnLabel] = settingReturnLabel;

	// -------------
	// SETTINGS LABEL
	// -------------
	GameObject* settingTitleLabel = GameObject::Instantiate("Settings Title Label", Layer::Menu);
	Text* settingTitleLabel_text = settingTitleLabel->AddComponent<Text>();
	settingTitleLabel_text->showOnScreen = true;
	settingTitleLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::Title),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Title)
	);
	settingTitleLabel->Render = [settingTitleLabel_text]() {
		settingTitleLabel_text->Render();
		};
	settingTitleLabel->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::Title), settingTitleLabel->transform->scale
	);
	uiElementMap[UIElementIndex::Title] = settingTitleLabel;

	// -------------
	// KEY BIND
	// -------------
	uiElementMap[UIElementIndex::KeyBindList] = GameObject::Instantiate<KeyBindUIGroup>("Key Bind UI Group", Layer::Menu);

}

void SettingsUI::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void SettingsUI::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

SettingsUI::SettingsUI() {

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

SettingsUI::~SettingsUI() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

}