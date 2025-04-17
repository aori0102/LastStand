/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <FirearmUpgradeUIGroup.h>

#include <iomanip>
#include <sstream>

#include <AudioManager.h>
#include <Firearm.h>
#include <FirearmUpgrade.h>
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int FirearmUpgradeUIGroup::UPGRADE_LABEL_SIZE = 24;
const int FirearmUpgradeUIGroup::UPGRADE_DESCRIPTION_SIZE = 14;
const int FirearmUpgradeUIGroup::UPGADE_COST_SIZE = 14;
const int FirearmUpgradeUIGroup::UPGADE_AMOUNT_DECIMAL = 2;
const int FirearmUpgradeUIGroup::NO_MORE_UPGRADE_FONT_SIZE = 20;
const float FirearmUpgradeUIGroup::UPGRADE_LABEL_OFFSET_Y = 50.0f;
const float FirearmUpgradeUIGroup::UPGRADE_COST_OFFSET_Y = 70.0f;
const std::string FirearmUpgradeUIGroup::COST_PREFIX = "Cost: ";
const std::string FirearmUpgradeUIGroup::NO_MORE_UPGRADE_MESSAGE = "All upgrade purchased!";

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmUpgradeUIGroup::InitializeUI() {

	frame = GameObject::Instantiate("Firearm Upgrade UI Frame", Layer::Menu);
	Image* frame_image = frame->AddComponent<Image>();
	frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlot), true);
	frame_image->showOnScreen = true;
	Button* frame_button = frame->AddComponent<Button>();
	frame_button->backgroundColor = Color::TRANSPARENT;
	frame_button->OnClick = [this]() {
		Shop::Instance()->BuyUpgrade(firearmAttributeIndex);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	frame_button->OnMouseEnter = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlotHovered), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	frame_button->OnMouseLeave = [frame_image]() {
		frame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlot), true);
		};
	frame->Render = [frame_image]() {
		frame_image->Render();
		};

	upgradeLabel = GameObject::Instantiate("Upgrade Label", Layer::Menu);
	Text* upgradeLabel_text = upgradeLabel->AddComponent<Text>();
	upgradeLabel_text->LoadText("Upgrade label", Color::WHITE, UPGRADE_LABEL_SIZE);
	upgradeLabel_text->showOnScreen = true;
	upgradeLabel->transform->position = transform->position + Vector2::up * UPGRADE_LABEL_OFFSET_Y;
	upgradeLabel->Render = [upgradeLabel_text]() {
		upgradeLabel_text->Render();
		};

	upgradeDescription = GameObject::Instantiate("Upgrade Description", Layer::Menu);
	Text* upgradeDescription_text = upgradeDescription->AddComponent<Text>();
	upgradeDescription_text->LoadText("Upgrade description", Color::WHITE, UPGRADE_DESCRIPTION_SIZE);
	upgradeDescription_text->showOnScreen = true;
	upgradeDescription->transform->position = transform->position;
	upgradeDescription->Render = [upgradeDescription_text]() {
		upgradeDescription_text->Render();
		};

	upgradeCost = GameObject::Instantiate("Upgrade Cost", Layer::Menu);
	Text* upgradeCost_text = upgradeCost->AddComponent<Text>();
	upgradeCost_text->LoadText(COST_PREFIX, Color::WHITE, UPGADE_COST_SIZE);
	upgradeCost_text->showOnScreen = true;
	upgradeCost->transform->position = transform->position + Vector2::down * UPGRADE_COST_OFFSET_Y;
	upgradeCost->Render = [upgradeCost_text]() {
		upgradeCost_text->Render();
		};

	noMoreUpgrade = GameObject::Instantiate("Firearm Upgrade UI No Upgrade", Layer::Menu);
	Text* noMoreUpgrade_text = noMoreUpgrade->AddComponent<Text>();
	noMoreUpgrade_text->showOnScreen = true;
	noMoreUpgrade_text->LoadText(NO_MORE_UPGRADE_MESSAGE, Color::WHITE, NO_MORE_UPGRADE_FONT_SIZE);
	noMoreUpgrade->transform->position = frame->transform->position;
	noMoreUpgrade->Render = [noMoreUpgrade_text]() {
		noMoreUpgrade_text->Render();
		};
	noMoreUpgrade->Disable();

}

void FirearmUpgradeUIGroup::Show() {

	if (upgradeAvailable) {

		upgradeCost->Enable();
		upgradeDescription->Enable();

	} else
		noMoreUpgrade->Enable();

	upgradeLabel->Enable();
	frame->Enable();

}

void FirearmUpgradeUIGroup::Hide() {

	upgradeLabel->Disable();
	upgradeDescription->Disable();
	upgradeCost->Disable();
	frame->Disable();
	noMoreUpgrade->Disable();

}

void FirearmUpgradeUIGroup::UpdateDescription() {

	std::stringstream ss;
	ss << descriptionPrefix << std::fixed << std::setprecision(UPGADE_AMOUNT_DECIMAL) << upgradeAmount << descriptionSuffix;

	upgradeDescription->GetComponent<Text>()->LoadText(ss.str(), Color::WHITE, UPGRADE_DESCRIPTION_SIZE);

}

FirearmUpgradeUIGroup::FirearmUpgradeUIGroup() {

	firearmAttributeIndex = FirearmAttributeIndex::Damage;

	upgradeAvailable = true;
	upgradeAmount = 0.0f;
	descriptionPrefix = "";
	descriptionSuffix = "";

	InitializeUI();

	OnEnabled = [this]() { Show(); };
	OnDisabled = [this]() { Hide(); };

}

void FirearmUpgradeUIGroup::SetAttribute(FirearmAttributeIndex initFirearmAttributeIndex) {

	firearmAttributeIndex = initFirearmAttributeIndex;

}

void FirearmUpgradeUIGroup::SetLabel(std::string label) {

	upgradeLabel->GetComponent<Text>()->LoadText(label, Color::WHITE, UPGRADE_LABEL_SIZE);

}

void FirearmUpgradeUIGroup::SetDescriptionPrefix(std::string prefix) {

	descriptionPrefix = prefix;

	UpdateDescription();

}

void FirearmUpgradeUIGroup::SetDescriptionSuffix(std::string suffix) {

	descriptionSuffix = suffix;

	UpdateDescription();

}

void FirearmUpgradeUIGroup::SetPosition(Vector2 positionInSDL) {

	frame->transform->position = Math::SDLToC00(positionInSDL, frame->transform->scale);
	upgradeLabel->transform->position = frame->transform->position + Vector2::up * UPGRADE_LABEL_OFFSET_Y;
	upgradeDescription->transform->position = frame->transform->position;
	upgradeCost->transform->position = frame->transform->position + Vector2::down * UPGRADE_COST_OFFSET_Y;
	noMoreUpgrade->transform->position = frame->transform->position;

}

void FirearmUpgradeUIGroup::SetUpgrade(UpgradeNode* upgrade) {

	if (upgrade == nullptr) {
		
		upgradeCost->Disable();
		upgradeDescription->Disable();
		noMoreUpgrade->Enable();
		upgradeAvailable = false;

		return;

	}

	upgradeAvailable = true;

	upgradeCost->GetComponent<Text>()->LoadText(COST_PREFIX + std::to_string(upgrade->cost), Color::WHITE, UPGADE_COST_SIZE);
	upgradeAmount = upgrade->amount;

	UpdateDescription();

}