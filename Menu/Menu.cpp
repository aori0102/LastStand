#include <Menu.h>

#include <iostream>
#include <exception>

#include <GameCore.h>
#include <GameManager.h>
#include <MediaManager.h>
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
		UI_TEXT_MAP.at(UIElementIndex::PlayLabel), Color::WHITE, MENU_BUTTON_FONT_SIZE
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
		std::cout << "Settings Button Clicked!" << std::endl;
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
		UI_TEXT_MAP.at(UIElementIndex::SettingsLabel), Color::WHITE, MENU_BUTTON_FONT_SIZE
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
		UI_TEXT_MAP.at(UIElementIndex::QuitLabel), Color::WHITE, MENU_BUTTON_FONT_SIZE
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
		GameCore::GetVersionString(), Color::WHITE, VERSION_FONT_SIZE
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

Menu::Menu() {

	if (instance)
		throw std::exception("Menu can only have one instance!");

	instance = this;

	InitializeMenu();

}

Menu::~Menu() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	instance = nullptr;

}

Menu* Menu::Instance() { return instance; }