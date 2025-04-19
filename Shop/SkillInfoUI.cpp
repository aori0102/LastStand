/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <SkillInfoUI.h>

#include <string>

#include <MediaManager.h>
#include <Shop.h>
#include <SkillList.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float SkillInfoUI::BUTTON_COST_LABEL_OFFSET = -7.0f;
const float SkillInfoUI::BUTTON_POINT_ICON_OFFSET = 13.0f;
const int SkillInfoUI::COST_LABEL_FONT_SIZE = 32;
const int SkillInfoUI::SKILL_DESCRIPTION_FONT_SIZE = 15;
const int SkillInfoUI::SKILL_LABEL_FONT_SIZE = 24;
const int SkillInfoUI::FRAME_UNSELECTED_MESSAGE_FONT_SIZE = 32;
const std::string SkillInfoUI::FRAME_UNSELECTED_MESSAGE = "Select a skill to view information.";
const Vector2 SkillInfoUI::FRAME_POSITION = Vector2(160.0f, 214.0f);
const Vector2 SkillInfoUI::ICON_FRAME_POSITION = Vector2(170.0f, 219.0f);
const Vector2 SkillInfoUI::BUTTON_FRAME_POSITION = Vector2(956.0f, 229.0f);
const Vector2 SkillInfoUI::SKILL_DESCRIPTION_OFFSET = Vector2(0.0f, -31.0f);
const Vector2 SkillInfoUI::SKILL_LABEL_OFFSET = Vector2(117.0f, -10.0f);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void SkillInfoUI::UpdateSkillInfo(SkillInfo info) {

	showingSkill = true;

	buttonCostLabel->GetComponent<Text>()->LoadText(
		std::to_string(info.skillPoint), Color::WHITE, COST_LABEL_FONT_SIZE
		);

	Text* skillLabel_text = skillLabel->AddComponent<Text>();
	skillLabel_text->LoadText(info.name, Color::WHITE, SKILL_LABEL_FONT_SIZE);
	skillLabel_text->showOnScreen = true;
	Align::Left(skillLabel->transform, frame->transform);
	Align::Top(skillLabel->transform, frame->transform);
	skillLabel->transform->position += SKILL_LABEL_OFFSET;

	Text* skillDescription_text = skillDescription->AddComponent<Text>();
	skillDescription_text->LoadText(info.description, Color::WHITE, SKILL_DESCRIPTION_FONT_SIZE);
	skillDescription_text->showOnScreen = true;
	Align::Left(skillDescription->transform, skillLabel->transform);
	Align::Top(skillDescription->transform, skillLabel->transform);
	skillDescription->transform->position += SKILL_DESCRIPTION_OFFSET;

	skillVisual->GetComponent<Image>()->LinkSprite(
		MediaManager::Instance()->GetUISprite(info.skillVisualIndex), true
	);

}

void SkillInfoUI::Show() {

	frame->Enable();
	iconFrame->Enable();
	buyButton->Enable();
	buttonCostLabel->Enable();
	buttonIcon->Enable();
	skillLabel->Enable();
	skillDescription->Enable();
	frameUnselected->Enable();
	frameUnselectedMessage->Enable();
	skillVisual->Enable();

}

void SkillInfoUI::Hide() {

	frame->Disable();
	iconFrame->Disable();
	buyButton->Disable();
	buttonCostLabel->Disable();
	buttonIcon->Disable();
	skillLabel->Disable();
	skillDescription->Disable();
	frameUnselected->Disable();
	frameUnselectedMessage->Disable();
	skillVisual->Disable();

}

SkillInfoUI::SkillInfoUI() {

	showingSkill = false;

	frame = GameObject::Instantiate("Skill Board Frame", Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillInfoBoard), true);
	frame_image->showOnScreen = true;
	frame_image->transform->position = Math::SDLToC00(
		FRAME_POSITION, frame_image->transform->scale
	);

	iconFrame = GameObject::Instantiate("Skill Info Icon Frame", Layer::Menu);
	Image* iconFrame_image = iconFrame->AddComponent<Image>();
	iconFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillIconFrame), true);
	iconFrame_image->showOnScreen = true;
	iconFrame_image->transform->position = Math::SDLToC00(
		ICON_FRAME_POSITION, iconFrame_image->transform->scale
	);

	buyButton = GameObject::Instantiate("Skill Info Button", Layer::Menu);
	Image* buyButton_image = buyButton->AddComponent<Image>();
	buyButton_image->showOnScreen = true;
	buyButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillBuyButton), true);
	Button* buyButton_button = buyButton->AddComponent<Button>();
	buyButton_button->backgroundColor = Color::TRANSPARENT;
	buyButton_button->transform->position = Math::SDLToC00(
		BUTTON_FRAME_POSITION, buyButton_button->transform->scale
	);
	buyButton_button->OnClick = [this]() {
		if (!IsActive() || !showingSkill)
			return false;
		Shop::Instance()->BuySkillNode();
		return true;
		};

	buttonCostLabel = GameObject::Instantiate("Skill Info Cost Label", Layer::Menu);
	Text* buttonCostLabel_text = buttonCostLabel->AddComponent<Text>();
	buttonCostLabel_text->LoadText("", Color::WHITE, COST_LABEL_FONT_SIZE);
	buttonCostLabel_text->showOnScreen = true;
	Align::Right(buttonCostLabel_text->transform, buyButton->transform);
	Align::MiddleVertically(buttonCostLabel_text->transform, buyButton->transform);
	buttonCostLabel_text->transform->position.x += BUTTON_COST_LABEL_OFFSET;

	buttonIcon = GameObject::Instantiate("Skill Info Icon Frame", Layer::Menu);
	Image* buttonIcon_image = buttonIcon->AddComponent<Image>();
	buttonIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_SkillPointIcon), true);
	buttonIcon_image->showOnScreen = true;
	Align::Left(buttonIcon_image->transform, buyButton->transform);
	Align::MiddleVertically(buttonIcon_image->transform, buyButton->transform);
	buttonIcon_image->transform->position.x += BUTTON_POINT_ICON_OFFSET;

	skillLabel = GameObject::Instantiate("Skill Label", Layer::Menu);
	Text* skillLabel_text = skillLabel->AddComponent<Text>();
	skillLabel_text->LoadText("<Skill Label>", Color::WHITE, SKILL_LABEL_FONT_SIZE);
	skillLabel_text->showOnScreen = true;
	Align::Left(skillLabel->transform, frame->transform);
	Align::Top(skillLabel->transform, frame->transform);
	skillLabel->transform->position += SKILL_LABEL_OFFSET;

	skillDescription = GameObject::Instantiate("Skill Description", Layer::Menu);
	Text* skillDescription_text = skillDescription->AddComponent<Text>();
	skillDescription_text->LoadText("<Skill Description>", Color::WHITE, SKILL_DESCRIPTION_FONT_SIZE);
	skillDescription_text->showOnScreen = true;
	Align::Left(skillDescription->transform, skillLabel->transform);
	Align::Top(skillDescription->transform, skillLabel->transform);
	skillDescription->transform->position += SKILL_DESCRIPTION_OFFSET;

	frameUnselected = GameObject::Instantiate("Skill Info Frame Unselected", Layer::Menu);
	Image* frameUnselected_image = frameUnselected->AddComponent<Image>();
	frameUnselected_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_SkillInfoBoardUnselected), true);
	frameUnselected_image->showOnScreen = true;
	frameUnselected->transform->position = frame->transform->position;

	frameUnselectedMessage = GameObject::Instantiate("Skill Info Frame Unselected Message", Layer::Menu);
	Text* frameUnselected_text = frameUnselectedMessage->AddComponent<Text>();
	frameUnselected_text->showOnScreen = true;
	frameUnselected_text->LoadText(FRAME_UNSELECTED_MESSAGE, Color::WHITE, FRAME_UNSELECTED_MESSAGE_FONT_SIZE);
	frameUnselectedMessage->transform->position = frame->transform->position;

	skillVisual = GameObject::Instantiate("Skill Info Icon Visual", Layer::Menu);
	Image* skillVisual_image = skillVisual->AddComponent<Image>();
	skillVisual_image->showOnScreen = true;
	skillVisual->transform->position = iconFrame->transform->position;

	Render = [this, skillVisual_image, frameUnselected_image, frameUnselected_text, buttonIcon_image, buttonCostLabel_text, buyButton_image, iconFrame_image, frame_image, skillLabel_text, skillDescription_text]() {
		frame_image->Render();
		if (!showingSkill) {
			frameUnselected_image->Render();
			frameUnselected_text->Render();
			return;
		}
		buttonIcon_image->Render();
		buttonCostLabel_text->Render();
		iconFrame_image->Render();
		buyButton_image->Render();
		skillLabel_text->Render();
		skillDescription_text->Render();
		skillVisual_image->Render();
		};

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}