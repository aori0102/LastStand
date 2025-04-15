#include <Menu.h>

#include <iostream>
#include <exception>

#include <AudioManager.h>
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
		GameManager::Instance()->SwitchScene(SceneIndex::InGame);
		GameManager::Instance()->UnfreezeGame();
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	playButton_button->OnMouseEnter = [playButton_image]() {
		playButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button_Selected), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	playButton_button->OnMouseLeave = [playButton_image]() {
		playButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
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
		GameManager::Instance()->SwitchScene(SceneIndex::Settings);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	settingsButton_button->OnMouseEnter = [settingsButton_image]() {
		settingsButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button_Selected), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	settingsButton_button->OnMouseLeave = [settingsButton_image]() {
		settingsButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
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
		GameCore::QuitGame();
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	quitButton_button->OnMouseEnter = [quitButton_image]() {
		quitButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button_Selected), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	quitButton_button->OnMouseLeave = [quitButton_image]() {
		quitButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
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

}

void Menu::Show() {

	uiElementMap.at(UIElementIndex::PlayButton)->Enable();
	uiElementMap.at(UIElementIndex::SettingsButton)->Enable();
	uiElementMap.at(UIElementIndex::QuitButton)->Enable();
	uiElementMap.at(UIElementIndex::PlayLabel)->Enable();
	uiElementMap.at(UIElementIndex::QuitLabel)->Enable();
	uiElementMap.at(UIElementIndex::SettingsLabel)->Enable();
	uiElementMap.at(UIElementIndex::Title)->Enable();
	uiElementMap.at(UIElementIndex::VersionLabel)->Enable();

}

void Menu::Hide() {

	uiElementMap.at(UIElementIndex::PlayButton)->Disable();
	uiElementMap.at(UIElementIndex::SettingsButton)->Disable();
	uiElementMap.at(UIElementIndex::QuitButton)->Disable();
	uiElementMap.at(UIElementIndex::PlayLabel)->Disable();
	uiElementMap.at(UIElementIndex::QuitLabel)->Disable();
	uiElementMap.at(UIElementIndex::SettingsLabel)->Disable();
	uiElementMap.at(UIElementIndex::Title)->Disable();
	uiElementMap.at(UIElementIndex::VersionLabel)->Disable();

}

Menu::Menu() {

	if (instance)
		throw std::exception("Menu can only have one instance!");

	instance = this;

	InitializeMenu();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

Menu::~Menu() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	instance = nullptr;

}

Menu* Menu::Instance() { return instance; }