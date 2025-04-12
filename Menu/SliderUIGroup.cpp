#include <SliderUIGroup.h>

#include <iomanip>
#include <sstream>

#include <GameCore.h>
#include <MediaManager.h>
#include <Texture.h>

const int SliderUIGroup::LABEL_FONT_SIZE = 20;
const int SliderUIGroup::VALUE_FONT_SIZE = 16;
const float SliderUIGroup::SLIDER_OFFSET = 189.0f;
const float SliderUIGroup::VALUE_OFFSET = 500.0f;
const std::string SliderUIGroup::VALUE_SUFFIX = "%";
const Vector2 SliderUIGroup::GROUP_SCALE = Vector2(553.0f, 24.0f);

void SliderUIGroup::InitializeUI() {

	emptyFormatFrame = GameObject::Instantiate("Slider Empty Format Frame", Layer::Menu);
	emptyFormatFrame->transform->scale = GROUP_SCALE;

	label = GameObject::Instantiate("Setting Slider Label", Layer::Menu);
	Text* label_text = label->AddComponent<Text>();
	label_text->showOnScreen = true;
	label_text->LoadText("Slider Label", Color::WHITE, LABEL_FONT_SIZE);
	Align::Left(label->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(label->transform, emptyFormatFrame->transform);
	label->Render = [this, label_text]() {
		if (IsActive())
			label_text->Render();
		};

	valueLabel = GameObject::Instantiate("Setting Slider Value Lable", Layer::Menu);
	Text* valueLabel_text = valueLabel->AddComponent<Text>();
	valueLabel_text->showOnScreen = true;
	valueLabel_text->LoadText("100%", Color::WHITE, VALUE_FONT_SIZE);
	Align::Left(valueLabel->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(valueLabel->transform, emptyFormatFrame->transform);
	valueLabel->transform->position.x += VALUE_OFFSET;
	valueLabel->Render = [this, valueLabel_text]() {
		if (IsActive())
			valueLabel_text->Render();
		};

	sliderBar = GameObject::Instantiate("Setting Slider Bar", Layer::Menu);
	Image* sliderBar_image = sliderBar->AddComponent<Image>();
	sliderBar_image->showOnScreen = true;
	sliderBar_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_Slider), true);
	Align::Left(sliderBar->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(sliderBar->transform, emptyFormatFrame->transform);
	sliderBar->transform->position.x += SLIDER_OFFSET;
	sliderBar->Render = [this, sliderBar_image]() {
		if (IsActive())
			sliderBar_image->Render();
		};

	sliderNob = GameObject::Instantiate("Setting Slider Nob", Layer::Menu);
	Image* sliderNob_image = sliderNob->AddComponent<Image>();
	sliderNob_image->showOnScreen = true;
	sliderNob_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_SliderButton), true);
	Button* sliderNob_button = sliderNob->AddComponent<Button>();
	sliderNob_button->backgroundColor = Color::TRANSPARENT;
	sliderNob_button->OnMouseBeginHold = [this, sliderNob_image]() {
		if (!IsActive())
			return;

		isSelected = true;
		sliderNob_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_SliderButtonSelected), true);

		};
	sliderNob->transform->position = sliderBar->transform->position + sliderBar->transform->scale;
	Align::MiddleVertically(sliderNob->transform, sliderBar->transform);
	sliderNob->Render = [this, sliderNob_image]() {
		if (IsActive())
			sliderNob_image->Render();
		};

}

void SliderUIGroup::Show() {

	emptyFormatFrame->Enable();
	label->Enable();
	sliderBar->Enable();
	sliderNob->Enable();
	valueLabel->Enable();

}

void SliderUIGroup::Hide() {

	emptyFormatFrame->Disable();
	label->Disable();
	sliderBar->Disable();
	sliderNob->Disable();
	valueLabel->Disable();

}

SliderUIGroup::SliderUIGroup() {

	OnValueUpdated = [](float) {};

	isSelected = false;

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

SliderUIGroup::~SliderUIGroup() {

	GameObject::Destroy(emptyFormatFrame);
	emptyFormatFrame = nullptr;

	GameObject::Destroy(label);
	label = nullptr;

	GameObject::Destroy(valueLabel);
	valueLabel = nullptr;

	GameObject::Destroy(sliderBar);
	sliderBar = nullptr;

	GameObject::Destroy(sliderNob);
	sliderNob = nullptr;

}

void SliderUIGroup::SetPosition(Vector2 positionInSDL) {

	emptyFormatFrame->transform->position = Math::SDLToC00(positionInSDL, GROUP_SCALE);

	Align::Left(label->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(label->transform, emptyFormatFrame->transform);

	Align::Left(valueLabel->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(valueLabel->transform, emptyFormatFrame->transform);
	valueLabel->transform->position.x += VALUE_OFFSET;

	Align::Left(sliderBar->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(sliderBar->transform, emptyFormatFrame->transform);
	sliderBar->transform->position.x += SLIDER_OFFSET;

	Align::Left(sliderNob->transform, emptyFormatFrame->transform);
	Align::MiddleVertically(sliderNob->transform, emptyFormatFrame->transform);
	sliderNob->transform->position.x = (sliderBar->transform->position + sliderBar->transform->scale * 0.5f).x;

}

void SliderUIGroup::SetSliderLabel(std::string sliderLable) {

	label->GetComponent<Text>()->LoadText(sliderLable, Color::WHITE, LABEL_FONT_SIZE);

}

void SliderUIGroup::SetValue(float value) {

	value = Math::Clamp(value, 0.0f, 1.0f);

	OnValueUpdated(value);

	sliderNob->transform->position.x = sliderBar->transform->position.x + (value - 0.5f) * sliderBar->transform->scale.x;

	std::stringstream ss;
	ss << std::fixed << std::setprecision(0) << value * 100.0f << VALUE_SUFFIX;
	valueLabel->GetComponent<Text>()->LoadText(ss.str(), Color::WHITE, VALUE_FONT_SIZE);

}

void SliderUIGroup::Update() {

	if (!isSelected)
		return;

	// Mouse left
	if (GameCore::GetMouseState(MouseButton::Left).canceled) {

		isSelected = false;
		sliderNob->GetComponent<Image>()->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::MenuSetting_SliderButton), true);

	}

	// Mouse is holding down

	float mousePositionX = Math::SDLToC00(GameCore::GetMouseInput(), Vector2::zero).x;
	float value = (mousePositionX - (sliderBar->transform->position - sliderBar->transform->scale / 2.0f).x) 
		/ sliderBar->transform->scale.x;

	SetValue(value);

}