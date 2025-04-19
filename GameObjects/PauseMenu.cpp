/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <PauseMenu.h>

#include <GameManager.h>
#include <InventoryUI.h>
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

PauseMenu* PauseMenu::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void PauseMenu::InitializeUI() {

	// -----------------
	// FRAME
	// -----------------
	GameObject* frame = GameObject::Instantiate("Pause Menu Frame", Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_PauseFrame), true);
	frame->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIElementIndex::Frame), frame->transform->scale);
	frame->Render = [frame_image]() {
		frame_image->Render();
		};
	uiElementMap[UIElementIndex::Frame] = frame;

	// -----------------
	// TITLE
	// -----------------
	GameObject* title = GameObject::Instantiate("Pause Menu Title", Layer::Menu);
	Text* title_text = title->AddComponent<Text>();
	title_text->showOnScreen = true;
	title_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::Title), Color::WHITE, TITLE_FONT_SIZE);
	title->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIElementIndex::Title), title->transform->scale);
	title->Render = [title_text]() {
		title_text->Render();
		};
	uiElementMap[UIElementIndex::Title] = title;

	// -----------------
	// RESUME BUTTON
	// -----------------
	GameObject* resumeButton = GameObject::Instantiate("Pause Menu Resume Button", Layer::Menu);
	Image* resumeButton_image = resumeButton->AddComponent<Image>();
	resumeButton_image->showOnScreen = true;
	resumeButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_PauseMenuButton),true);
	Button* resumeButton_button = resumeButton->AddComponent<Button>();
	resumeButton_button->backgroundColor = Color::TRANSPARENT;
	resumeButton_button->OnClick = []() {
		GameManager::Instance()->SwitchScene(SceneIndex::InGame);
		GameManager::Instance()->UnfreezeGame();
		return true;
		};
	resumeButton->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIElementIndex::ResumeButton), resumeButton->transform->scale);
	resumeButton->Render = [resumeButton_image]() {
		resumeButton_image->Render();
		};
	uiElementMap[UIElementIndex::ResumeButton] = resumeButton;

	// -----------------
	// SETTINGS BUTTON
	// -----------------
	GameObject* settingsButton = GameObject::Instantiate("Pause Menu Settings Button", Layer::Menu);
	Image* settingsButton_image = settingsButton->AddComponent<Image>();
	settingsButton_image->showOnScreen = true;
	settingsButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_PauseMenuButton), true);
	Button* settingsButton_button = settingsButton->AddComponent<Button>();
	settingsButton_button->backgroundColor = Color::TRANSPARENT;
	settingsButton_button->OnClick = []() {
		GameManager::Instance()->SwitchScene(SceneIndex::Settings);
		return true;
		};
	settingsButton->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIElementIndex::SettingsButton), settingsButton->transform->scale);
	settingsButton->Render = [settingsButton_image]() {
		settingsButton_image->Render();
		};
	uiElementMap[UIElementIndex::SettingsButton] = settingsButton;

	// -----------------
	// MAIN MENU BUTTON
	// -----------------
	GameObject* mainMenuButton = GameObject::Instantiate("Pause Menu Main Menu Button", Layer::Menu);
	Image* mainMenuButton_image = mainMenuButton->AddComponent<Image>();
	mainMenuButton_image->showOnScreen = true;
	mainMenuButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Menu_PauseMenuButton), true);
	Button* mainMenuButton_button = mainMenuButton->AddComponent<Button>();
	mainMenuButton_button->backgroundColor = Color::TRANSPARENT;
	mainMenuButton_button->OnClick = []() {
		GameManager::Instance()->SwitchScene(SceneIndex::MainMenu);
		return true;
		};
	mainMenuButton->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIElementIndex::MainMenuButton), mainMenuButton->transform->scale);
	mainMenuButton->Render = [mainMenuButton_image]() {
		mainMenuButton_image->Render();
		};
	uiElementMap[UIElementIndex::MainMenuButton] = mainMenuButton;

	// -----------------
	// RESUME LABEL
	// -----------------
	GameObject* resumeLabel = GameObject::Instantiate("Pause Menu Resume Label", Layer::Menu);
	Text* resumeLabel_text = resumeLabel->AddComponent<Text>();
	resumeLabel_text->showOnScreen = true;
	resumeLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::ResumeLabel), Color::WHITE, TITLE_FONT_SIZE);
	resumeLabel->transform->position = resumeButton->transform->position;
	resumeLabel->Render = [resumeLabel_text]() {
		resumeLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ResumeLabel] = resumeLabel;

	// -----------------
	// SETTINGS LABEL
	// -----------------
	GameObject* settingsLabel = GameObject::Instantiate("Pause Menu Settings Label", Layer::Menu);
	Text* settingsLabel_text = settingsLabel->AddComponent<Text>();
	settingsLabel_text->showOnScreen = true;
	settingsLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::SettingsLabel), Color::WHITE, TITLE_FONT_SIZE);
	settingsLabel->transform->position = settingsButton->transform->position;
	settingsLabel->Render = [settingsLabel_text]() {
		settingsLabel_text->Render();
		};
	uiElementMap[UIElementIndex::SettingsLabel] = settingsLabel;

	// -----------------
	// RESUME LABEL
	// -----------------
	GameObject* mainMenuLabel = GameObject::Instantiate("Pause Menu Main Menu Label", Layer::Menu);
	Text* mainMenuLabel_text = mainMenuLabel->AddComponent<Text>();
	mainMenuLabel_text->showOnScreen = true;
	mainMenuLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::MainMenuLabel), Color::WHITE, TITLE_FONT_SIZE);
	mainMenuLabel->transform->position = mainMenuButton->transform->position;
	mainMenuLabel->Render = [mainMenuLabel_text]() {
		mainMenuLabel_text->Render();
		};
	uiElementMap[UIElementIndex::MainMenuLabel] = mainMenuLabel;

}

void PauseMenu::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

	Shop::Instance()->Disable();
	InventoryUI::Instance()->Disable();

}

void PauseMenu::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

PauseMenu::PauseMenu() {

	if (instance)
		throw std::exception("PauseMenu can only have one instance");

	instance = this;

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

PauseMenu::~PauseMenu() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

	instance = nullptr;

}

PauseMenu* PauseMenu::Instance() { return instance; }