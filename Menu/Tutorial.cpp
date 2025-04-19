/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Tutorial.h>

#include <GameCore.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <SDL.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const std::unordered_map<ActionIndex, std::string> Tutorial::KEY_BIND_PLACEHOLDER_MAP = {
	{ ActionIndex::MoveUp, "<Key_W>" },
	{ ActionIndex::MoveDown, "<Key_S>" },
	{ ActionIndex::MoveLeft, "<Key_A>" },
	{ ActionIndex::MoveRight, "<Key_D>" },
	{ ActionIndex::Reload, "<Key_R>" },
	{ ActionIndex::Sprint, "<Key_LeftShift>" },
	{ ActionIndex::ToggleInventory, "<Key_I>" },
	{ ActionIndex::ToggleShop, "<Key_Tab>" },
};

Tutorial* Tutorial::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Tutorial::InitializeUI() {

	/// -----------------
	/// TITLE
	/// -----------------
	GameObject* title = GameObject::Instantiate("Tutorial Title", Layer::Menu);
	Text* title_text = title->AddComponent<Text>();
	title_text->showOnScreen = true;
	title_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::Title), Color::WHITE, TITLE_FONT_SIZE);
	Align::Top(title->transform);
	Align::MiddleHorizontally(title->transform);
	title->transform->position += Vector2::down * TITLE_OFFSET_Y;
	title->Render = [title_text]() {
		title_text->Render();
		};
	uiElementMap[UIElementIndex::Title] = title;

	/// -----------------
	/// TUTORIAL MESSAGES
	/// -----------------
	float offset = 0.0f;
	for (int i = static_cast<int>(UIElementIndex::Move); i < static_cast<int>(UIElementIndex::Total); i++) {

		UIElementIndex uiIndex = static_cast<UIElementIndex>(i);

		GameObject* tutorialMessage = GameObject::Instantiate("Tutorial Message", Layer::Menu);
		Text* tutorialMessage_text = tutorialMessage->AddComponent<Text>();
		tutorialMessage_text->showOnScreen = true;
		tutorialMessage_text->LoadText(MESSAGE_PREFIX + UI_LABEL_MAP.at(uiIndex), Color::WHITE, TUTORIAL_FONT_SIZE);
		tutorialMessage->transform->position = Math::SDLToC00(
			STARTING_POSITION, tutorialMessage->transform->scale
		) + Vector2::down * offset;
		tutorialMessage->Render = [tutorialMessage_text]() {
			tutorialMessage_text->Render();
			};
		uiElementMap[uiIndex] = tutorialMessage;

		offset += MESSAGE_OFFSET_Y;

	}

	/// -----------------
	/// RETURN BUTTON
	/// -----------------
	GameObject* returnButton = GameObject::Instantiate("Tutorial Return Button", Layer::Menu);
	Image* returnButton_image = returnButton->AddComponent<Image>();
	returnButton_image->showOnScreen = true;
	returnButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_ReturnButton), true);
	Button* returnButton_button = returnButton->AddComponent<Button>();
	returnButton_button->backgroundColor = Color::TRANSPARENT;
	returnButton_button->OnClick = []() {
		GameManager::Instance()->SwitchToPreviousScene();
		return true;
		};
	returnButton->transform->position = Math::SDLToC00(RETURN_BUTTON_POSITION, returnButton->transform->scale);
	returnButton->Render = [returnButton_image]() {
		returnButton_image->Render();
		};
	uiElementMap[UIElementIndex::ReturnButton] = returnButton;

	/// -----------------
	/// RETURN BUTTON LABEL
	/// -----------------
	GameObject* returnButtonLabel = GameObject::Instantiate("Tutorial Return Button Label", Layer::Menu);
	Text* returnButtonLabel_text = returnButtonLabel->AddComponent<Text>();
	returnButtonLabel_text->showOnScreen = true;
	returnButtonLabel_text->LoadText(UI_LABEL_MAP.at(UIElementIndex::ReturnLabel), Color::WHITE, RETURN_LABEL_FONT_SIZE);
	returnButtonLabel->transform->position = returnButton->transform->position;
	returnButtonLabel->Render = [returnButtonLabel_text]() {
		returnButtonLabel_text->Render();
		};
	uiElementMap[UIElementIndex::ReturnLabel] = returnButtonLabel;

}

void Tutorial::UpdateUI() {

	float offset = 0.0f;
	for (int i = static_cast<int>(UIElementIndex::Move); i < static_cast<int>(UIElementIndex::Total); i++) {

		UIElementIndex uiIndex = static_cast<UIElementIndex>(i);

		GameObject* tutorialMessage = uiElementMap.at(uiIndex);
		tutorialMessage->transform->position = Math::SDLToC00(
			STARTING_POSITION, tutorialMessage->transform->scale
		) + Vector2::down * offset;

		offset += MESSAGE_OFFSET_Y;

	}

}

void Tutorial::Show() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Enable();

}

void Tutorial::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

Tutorial::Tutorial() {

	if (instance)
		throw std::exception("Tutorial can only have one instance!");

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

	instance = this;

}

Tutorial::~Tutorial() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		GameObject::Destroy(it->second);

	uiElementMap.clear();

	instance = nullptr;

}

void Tutorial::UpdateActionBinding(ActionIndex actionIndex) {

	switch (actionIndex) {

	case ActionIndex::MoveUp:
	case ActionIndex::MoveDown:
	case ActionIndex::MoveLeft:
	case ActionIndex::MoveRight: {

		std::string baseStr = UI_LABEL_MAP.at(UIElementIndex::Move);
		std::string message = baseStr.substr(
			0, baseStr.find(KEY_BIND_PLACEHOLDER_MAP.at(ActionIndex::MoveUp))
		);
		message += std::string(SDL_GetKeyName(GameCore::GetKeyBinded(ActionIndex::MoveUp))) + ", ";
		message += std::string(SDL_GetKeyName(GameCore::GetKeyBinded(ActionIndex::MoveLeft))) + ", ";
		message += std::string(SDL_GetKeyName(GameCore::GetKeyBinded(ActionIndex::MoveDown))) + ", ";
		message += std::string(SDL_GetKeyName(GameCore::GetKeyBinded(ActionIndex::MoveRight))) + ".";
		uiElementMap.at(UIElementIndex::Move)->GetComponent<Text>()->LoadText(
			MESSAGE_PREFIX+message, Color::WHITE, TUTORIAL_FONT_SIZE
		);

		break;

	}

	case ActionIndex::Reload: {

		std::string baseStr = UI_LABEL_MAP.at(UIElementIndex::Shoot);
		size_t index = baseStr.find(KEY_BIND_PLACEHOLDER_MAP.at(actionIndex));
		size_t size = KEY_BIND_PLACEHOLDER_MAP.at(actionIndex).size();
		std::string message = baseStr.substr(0, index);
		message += SDL_GetKeyName(GameCore::GetKeyBinded(actionIndex));
		message += baseStr.substr(index + size);

		uiElementMap.at(UIElementIndex::Shoot)->GetComponent<Text>()->LoadText(
			MESSAGE_PREFIX + message, Color::WHITE, TUTORIAL_FONT_SIZE
		);

		break;

	}

	case ActionIndex::Sprint: {

		std::string baseStr = UI_LABEL_MAP.at(UIElementIndex::Sprint);
		size_t index = baseStr.find(KEY_BIND_PLACEHOLDER_MAP.at(actionIndex));
		size_t size = KEY_BIND_PLACEHOLDER_MAP.at(actionIndex).size();
		std::string message = baseStr.substr(0, index);
		message += SDL_GetKeyName(GameCore::GetKeyBinded(actionIndex));
		message += baseStr.substr(index + size);

		uiElementMap.at(UIElementIndex::Sprint)->GetComponent<Text>()->LoadText(
			MESSAGE_PREFIX + message, Color::WHITE, TUTORIAL_FONT_SIZE
		);

		break;

	}

	case ActionIndex::ToggleInventory: {

		std::string baseStr = UI_LABEL_MAP.at(UIElementIndex::Inventory);
		size_t index = baseStr.find(KEY_BIND_PLACEHOLDER_MAP.at(actionIndex));
		size_t size = KEY_BIND_PLACEHOLDER_MAP.at(actionIndex).size();
		std::string message = baseStr.substr(0, index);
		message += SDL_GetKeyName(GameCore::GetKeyBinded(actionIndex));
		message += baseStr.substr(index + size);

		uiElementMap.at(UIElementIndex::Inventory)->GetComponent<Text>()->LoadText(
			MESSAGE_PREFIX + message, Color::WHITE, TUTORIAL_FONT_SIZE
		);

		break;

	}

	case ActionIndex::ToggleShop: {

		std::string baseStr = UI_LABEL_MAP.at(UIElementIndex::Shop);
		size_t index = baseStr.find(KEY_BIND_PLACEHOLDER_MAP.at(actionIndex));
		size_t size = KEY_BIND_PLACEHOLDER_MAP.at(actionIndex).size();
		std::string message = baseStr.substr(0, index);
		message += SDL_GetKeyName(GameCore::GetKeyBinded(actionIndex));
		message += baseStr.substr(index + size);

		uiElementMap.at(UIElementIndex::Shop)->GetComponent<Text>()->LoadText(
			MESSAGE_PREFIX + message, Color::WHITE, TUTORIAL_FONT_SIZE
		);

		break;

	}

	}

	UpdateUI();

}

Tutorial* Tutorial::Instance() { return instance; }