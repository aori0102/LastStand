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
#include <MediaManager.h>
#include <Shop.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int FirearmUpgradeUIGroup::UPGRADE_LABEL_SIZE = 24;
const int FirearmUpgradeUIGroup::UPGRADE_DESCRIPTION_SIZE = 14;
const int FirearmUpgradeUIGroup::UPGADE_COST_SIZE = 14;
const float FirearmUpgradeUIGroup::UPGRADE_LABEL_OFFSET_Y = 50.0f;
const float FirearmUpgradeUIGroup::UPGRADE_COST_OFFSET_Y = 70.0f;
const std::string FirearmUpgradeUIGroup::COST_PREFIX = "Cost: ";

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmUpgradeUIGroup::Show() {

	upgradeLabel->Enable();
	upgradeDescription->Enable();
	upgradeCost->Enable();

}

void FirearmUpgradeUIGroup::Hide() {

	upgradeLabel->Disable();
	upgradeDescription->Disable();
	upgradeCost->Disable();

}

void FirearmUpgradeUIGroup::UpdateDescription() {

	std::stringstream ss;
	ss << descriptionPrefix << std::fixed << std::setprecision(descriptionDecimalPlace) << upgradeAmount << descriptionSuffix;

	upgradeDescription->GetComponent<Text>()->LoadText(ss.str(), Color::WHITE, UPGRADE_DESCRIPTION_SIZE);

}

FirearmUpgradeUIGroup::FirearmUpgradeUIGroup() {

	firearmAttributeIndex = FirearmAttributeIndex::Damage;

	upgradeAmount = 0.0f;
	descriptionDecimalPlace = 0;
	descriptionPrefix = "";
	descriptionSuffix = "";

	Image* upgrade_image = AddComponent<Image>();
	upgrade_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlot), true);
	upgrade_image->showOnScreen = true;
	Button* upgrade_button = AddComponent<Button>();
	upgrade_button->backgroundColor = Color::TRANSPARENT;
	upgrade_button->OnClick = [this]() {
		Shop::Instance()->BuyUpgrade(firearmAttributeIndex);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Click);
		return true;
		};
	upgrade_button->OnMouseEnter = [upgrade_image]() {
		upgrade_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlotHovered), true);
		AudioManager::Instance()->PlayOneShot(MediaSFX::Clack);
		};
	upgrade_button->OnMouseLeave = [upgrade_image]() {
		upgrade_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmUpgradeSlot), true);
		};

	upgradeLabel = GameObject::Instantiate("Upgrade Label", Layer::Menu);
	Text* upgradeLabel_text = upgradeLabel->AddComponent<Text>();
	upgradeLabel_text->LoadText("Upgrade label", Color::WHITE, UPGRADE_LABEL_SIZE);
	upgradeLabel_text->showOnScreen = true;
	upgradeLabel_text->transform->position = transform->position + Vector2::up * UPGRADE_LABEL_OFFSET_Y;

	upgradeDescription = GameObject::Instantiate("Upgrade Description", Layer::Menu);
	Text* upgradeDescription_text = upgradeDescription->AddComponent<Text>();
	upgradeDescription_text->LoadText("Upgrade description", Color::WHITE, UPGRADE_DESCRIPTION_SIZE);
	upgradeDescription_text->showOnScreen = true;
	upgradeDescription_text->transform->position = transform->position;

	upgradeCost = GameObject::Instantiate("Upgrade Cost", Layer::Menu);
	Text* upgradeCost_text = upgradeCost->AddComponent<Text>();
	upgradeCost_text->LoadText(COST_PREFIX, Color::WHITE, UPGADE_COST_SIZE);
	upgradeCost_text->showOnScreen = true;
	upgradeCost_text->transform->position = transform->position + Vector2::down * UPGRADE_COST_OFFSET_Y;

	Render = [upgrade_image, upgradeLabel_text, upgradeDescription_text, upgradeCost_text]() {
		upgrade_image->Render();
		upgradeLabel_text->Render();
		upgradeDescription_text->Render();
		upgradeCost_text->Render();
		};

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

void FirearmUpgradeUIGroup::SetAmount(float amount, int decimalPlace) {

	upgradeAmount = amount;
	descriptionDecimalPlace = decimalPlace;

	UpdateDescription();

}

void FirearmUpgradeUIGroup::SetCost(int amount) {

	upgradeCost->GetComponent<Text>()->LoadText(COST_PREFIX + std::to_string(amount), Color::WHITE, UPGADE_COST_SIZE);

}

void FirearmUpgradeUIGroup::SetPosition(Vector2 positionInSDL) {

	transform->position = Math::SDLToC00(positionInSDL, transform->scale);
	upgradeLabel->transform->position = transform->position + Vector2::up * UPGRADE_LABEL_OFFSET_Y;
	upgradeDescription->transform->position = transform->position;
	upgradeCost->transform->position = transform->position + Vector2::down * UPGRADE_COST_OFFSET_Y;

}