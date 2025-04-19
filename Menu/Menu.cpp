/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

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

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

Menu* Menu::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Menu::InitializeMenu() {

	/// -------------
	/// TITLE
	/// -------------
	GameObject* title = GameObject::Instantiate("Menu Title", Layer::Menu);
	Image* title_image = title->AddComponent<Image>();
	title_image->showOnScreen = true;
	title_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Title), true);
	title->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::Title), title->transform->scale
	);
	title->Render = [title_image]() {
		title_image->Render();
		};
	uiElementMap[UIElementIndex::Title] = title;

	/// -------------
	/// PLAY BUTTON
	/// -------------
	GameObject* playButton = GameObject::Instantiate("Menu Play Button", Layer::Menu);
	Image* playButton_image = playButton->AddComponent<Image>();
	playButton_image->showOnScreen = true;
	playButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* playButton_button = playButton->AddComponent<Button>();
	playButton_button->backgroundColor = Color::TRANSPARENT;
	playButton_button->OnClick = []() {
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
		UI_POSITION_MAP.at(UIElementIndex::PlayButton), playButton->transform->scale
	);
	playButton->Render = [playButton_image]() {
		playButton_image->Render();
		};
	uiElementMap[UIElementIndex::PlayButton] = playButton;

	/// -------------
	/// PLAY LABEL
	/// -------------
	GameObject* playButtonLabel = GameObject::Instantiate("Menu Play Button Label", Layer::Menu);
	Text* playButtonLabel_text = playButtonLabel->AddComponent<Text>();
	playButtonLabel_text->showOnScreen = true;
	playButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::PlayLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::PlayLabel)
	);
	playButtonLabel->transform->position = playButton->transform->position;
	playButtonLabel->Render = [playButtonLabel_text]() {
		playButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::PlayLabel] = playButtonLabel;

	/// -------------
	/// SETTINGS BUTTON
	/// -------------
	GameObject* settingsButton = GameObject::Instantiate("Menu Settings Button", Layer::Menu);
	Image* settingsButton_image = settingsButton->AddComponent<Image>();
	settingsButton_image->showOnScreen = true;
	settingsButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* settingsButton_button = settingsButton->AddComponent<Button>();
	settingsButton_button->backgroundColor = Color::TRANSPARENT;
	settingsButton_button->OnClick = []() {
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
		UI_POSITION_MAP.at(UIElementIndex::SettingsButton), settingsButton->transform->scale
	);
	settingsButton->Render = [settingsButton_image]() {
		settingsButton_image->Render();
		};
	uiElementMap[UIElementIndex::SettingsButton] = settingsButton;

	/// -------------
	/// SETTINGS LABEL
	/// -------------
	GameObject* settingsButtonLabel = GameObject::Instantiate("Menu Settings Button Label", Layer::Menu);
	Text* settingsButtonLabel_text = settingsButtonLabel->AddComponent<Text>();
	settingsButtonLabel_text->showOnScreen = true;
	settingsButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::SettingsLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::SettingsLabel)
	);
	settingsButtonLabel->transform->position = settingsButton->transform->position;
	settingsButtonLabel->Render = [settingsButtonLabel_text]() {
		settingsButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::SettingsLabel] = settingsButtonLabel;

	/// -------------
	/// QUIT BUTTON
	/// -------------
	GameObject* quitButton = GameObject::Instantiate("Menu Quit Button", Layer::Menu);
	Image* quitButton_image = quitButton->AddComponent<Image>();
	quitButton_image->showOnScreen = true;
	quitButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_Button), true);
	Button* quitButton_button = quitButton->AddComponent<Button>();
	quitButton_button->backgroundColor = Color::TRANSPARENT;
	quitButton_button->OnClick = []() {
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
		UI_POSITION_MAP.at(UIElementIndex::QuitButton), quitButton->transform->scale
	);
	quitButton->Render = [quitButton_image]() {
		quitButton_image->Render();
		};
	uiElementMap[UIElementIndex::QuitButton] = quitButton;

	/// -------------
	/// QUIT LABEL
	/// -------------
	GameObject* quitButtonLabel = GameObject::Instantiate("Menu Quit Button Label", Layer::Menu);
	Text* quitButtonLabel_text = quitButtonLabel->AddComponent<Text>();
	quitButtonLabel_text->showOnScreen = true;
	quitButtonLabel_text->LoadText(
		UI_TEXT_MAP.at(UIElementIndex::QuitLabel), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::QuitLabel)
	);
	quitButtonLabel->transform->position = quitButton->transform->position;
	quitButtonLabel->Render = [quitButtonLabel_text]() {
		quitButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::QuitLabel] = quitButtonLabel;

	/// -------------
	/// VERSION LABEL
	/// -------------
	GameObject* versionLabel = GameObject::Instantiate("Menu Version Label", Layer::Menu);
	Text* versionLabel_text = versionLabel->AddComponent<Text>();
	versionLabel_text->showOnScreen = true;
	versionLabel_text->LoadText(
		GameCore::GetVersionString(), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::VersionLabel)
	);
	Align::Right(versionLabel->transform);
	Align::Bottom(versionLabel->transform);
	versionLabel->transform->position += UI_POSITION_MAP.at(UIElementIndex::VersionLabel);
	versionLabel->Render = [versionLabel_text]() {
		versionLabel_text->Render();
		};
	uiElementMap[UIElementIndex::VersionLabel] = versionLabel;

	/// -------------
	/// TUTORIAL BUTTON
	/// -------------
	GameObject* tutorialButton = GameObject::Instantiate("Menu Tutorial Button", Layer::Menu);
	Image* tutorialButton_image = tutorialButton->AddComponent<Image>();
	tutorialButton_image->showOnScreen = true;
	tutorialButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_TutorialButton), true);
	Button* tutorialButton_button = tutorialButton->AddComponent<Button>();
	tutorialButton_button->backgroundColor = Color::TRANSPARENT;
	tutorialButton_button->OnClick = []() {
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		GameManager::Instance()->SwitchScene(SceneIndex::Tutorial);
		return true;
		};
	tutorialButton_button->OnMouseEnter = [tutorialButton_image]() {
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		tutorialButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_TutorialButton_Selected), true);
		};
	tutorialButton_button->OnMouseLeave = [tutorialButton_image]() {
		tutorialButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_TutorialButton), true);
		};
	tutorialButton->transform->position = Math::SDLToC00(
		UI_POSITION_MAP.at(UIElementIndex::TutorialButton), tutorialButton->transform->scale
	);
	tutorialButton->Render = [tutorialButton_image]() {
		tutorialButton_image->Render();
		};
	uiElementMap[UIElementIndex::TutorialButton] = tutorialButton;

}

void Menu::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void Menu::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

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