#include <KeyBindSingleUIGroup.h>

#include <GameCore.h>
#include <MediaManager.h>
#include <Texture.h>

const int KeyBindSingleUIGroup::LABEL_FONT_SIZE = 16;
const int KeyBindSingleUIGroup::KEY_FONT_SIZE = 12;
const float KeyBindSingleUIGroup::LABEL_OFFSET = -11.0f;

void KeyBindSingleUIGroup::UpdateVisual(std::string keyString) {

	// Update visual
	frame->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_KeyBindingFrame), true
	);
	keyLabel->GetComponent<Text>()->LoadText(
		keyString, Color::WHITE, KEY_FONT_SIZE
	);
	keyLabel->transform->position = frame->transform->position;

}

void KeyBindSingleUIGroup::Show() {

	label->Enable();
	frame->Enable();
	keyLabel->Enable();

}

void KeyBindSingleUIGroup::Hide() {

	label->Disable();
	frame->Disable();
	keyLabel->Disable();

}

KeyBindSingleUIGroup::KeyBindSingleUIGroup() {

	bindAction = ActionIndex::MoveUp;

	isSelected = false;

	frame = GameObject::Instantiate("Key Bind Single UI Group", Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->showOnScreen = true;
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_KeyBindingFrame), true);
	Button* frame_button = frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [this, frame_image]() {
		if (!IsActive())
			return false;
		isSelected = true;
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_KeyBindingFrameSelected), true);
		return true;
		};
	frame->Render = [this, frame_image]() {
		if (IsActive())
			frame_image->Render();
		};

	label = GameObject::Instantiate("Key Bind Single UI Group", Layer::Menu);
	Text* label_text = label->AddComponent<Text>();
	label_text->showOnScreen = true;
	label_text->LoadText("Label", Color::WHITE, LABEL_FONT_SIZE);
	Align::Left(label->transform, frame->transform);
	Align::MiddleVertically(label->transform, frame->transform);
	label->transform->position.x += LABEL_OFFSET - label->transform->scale.x;
	label->Render = [this, label_text]() {
		if (IsActive())
			label_text->Render();
		};

	keyLabel = GameObject::Instantiate("Key Bind Single UI Group", Layer::Menu);
	Text* keyLabel_text = keyLabel->AddComponent<Text>();
	keyLabel_text->showOnScreen = true;
	keyLabel_text->LoadText("Key", Color::WHITE, KEY_FONT_SIZE);
	keyLabel->transform->position = frame->transform->position;
	keyLabel->Render = [this, keyLabel_text]() {
		if (IsActive())
			keyLabel_text->Render();
		};

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

KeyBindSingleUIGroup::~KeyBindSingleUIGroup() {

	GameObject::Destroy(label);
	label = nullptr;

	GameObject::Destroy(frame);
	frame = nullptr;

	GameObject::Destroy(keyLabel);
	keyLabel = nullptr;

}

void KeyBindSingleUIGroup::SetPosition(Vector2 positionInSDL) {

	frame->transform->position = Math::SDLToC00(positionInSDL, frame->transform->scale);
	keyLabel->transform->position = frame->transform->position;
	Align::Left(label->transform, frame->transform);
	Align::MiddleVertically(label->transform, frame->transform);
	label->transform->position.x += LABEL_OFFSET - label->transform->scale.x;

}

void KeyBindSingleUIGroup::SetLabel(std::string initLabel) {

	label->GetComponent<Text>()->LoadText(initLabel, Color::WHITE, LABEL_FONT_SIZE);
	Align::Left(label->transform, frame->transform);
	label->transform->position.x += LABEL_OFFSET - label->transform->scale.x;

}

void KeyBindSingleUIGroup::BindAction(ActionIndex initBindAction) {

	bindAction = initBindAction;

	UpdateVisual(SDL_GetKeyName(GameCore::GetKeyBinded(bindAction)));

}

void KeyBindSingleUIGroup::Update() {

	if (!isSelected)
		return;

	if (GameCore::IsAnyKeyPressed()) {

		// Set keybind
		GameCore::SetActionKeyBind(bindAction, GameCore::GetLastKey());

		UpdateVisual(GameCore::GetLastKeyInString());

		// Set flag
		isSelected = false;

	}

}