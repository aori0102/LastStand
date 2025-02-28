#include <Shop.h>
#include <Texture.h>
#include <Type.h>
#include <Game.h>
#include <Player.h>
#include <GameManager.h>
#include <string>
#include <sstream>
#include <iomanip>

// Settings
const Vector2 SHOP_BACKGROUND_SIZE = Vector2(800.0f, 500.0f);
const Vector2 BUY_BUTTON_SIZE = Vector2(150.0f, 70.0f);
const Vector2 NAVIGATION_BUTTON_SIZE = Vector2(250.0f, 60.0f);
const Vector2 NAVIGATION_BUTTON_OFFSET = Vector2(5.0f, 5.0f);
const Vector2 UPGRADE_BUTTON_SIZE = Vector2(700.0f, 80.0f);
const float UPGRADE_BUTTON_VERTICAL_OFFSET = 15.0f;
const float UPGRADE_BUTTON_TOP = 250.0f;

Shop::Shop(Player* initPlayer) {

	if (!initPlayer)
		throw new exception("Initialize shop with null player");

	linkedPlayer = initPlayer;

	shopMenuIndex = ShopMenuIndex::Firearm;

	showShop = false;

	InitializeUpgrades();
	InitializeUI();

}

void Shop::Update() {

	if (Game::GetKeyState(SDLK_TAB).started)
		showShop = !showShop;

	if (showShop) {

		linkedPlayer->DisableInteraction();
		Show();

		ShowCurrentMenu();

	} else {

		linkedPlayer->EnableInteraction();
		Hide();

		HideCurrentMenu();

	}

}

void Shop::Show() {

	background->Enable();

	menuNavigationButtonMap.at(ShopMenuIndex::Firearm)->button->Enable();
	menuNavigationButtonMap.at(ShopMenuIndex::Melee)->button->Enable();
	menuNavigationButtonMap.at(ShopMenuIndex::Utility)->button->Enable();

	firearmAttributeInfoMap.at(Firearm::Attribute::Damage)->Show();
	firearmAttributeInfoMap.at(Firearm::Attribute::ReloadTime)->Show();
	firearmAttributeInfoMap.at(Firearm::Attribute::MaxAmmo)->Show();
	firearmAttributeInfoMap.at(Firearm::Attribute::CriticalChance)->Show();

	firearmAttributeFrame->Enable();

}

void Shop::Hide() {

	background->Disable();

	menuNavigationButtonMap.at(ShopMenuIndex::Firearm)->button->Disable();
	menuNavigationButtonMap.at(ShopMenuIndex::Melee)->button->Disable();
	menuNavigationButtonMap.at(ShopMenuIndex::Utility)->button->Disable();

	firearmAttributeInfoMap.at(Firearm::Attribute::Damage)->Hide();
	firearmAttributeInfoMap.at(Firearm::Attribute::ReloadTime)->Hide();
	firearmAttributeInfoMap.at(Firearm::Attribute::MaxAmmo)->Hide();
	firearmAttributeInfoMap.at(Firearm::Attribute::CriticalChance)->Hide();

	firearmAttributeFrame->Disable();

}

void Shop::ShowCurrentMenu() {

	switch (shopMenuIndex) {

	case ShopMenuIndex::Firearm:

		firearmUpgradeUIGroupMap[Firearm::Attribute::Damage]->Show();
		firearmUpgradeUIGroupMap[Firearm::Attribute::ReloadTime]->Show();
		firearmUpgradeUIGroupMap[Firearm::Attribute::MaxAmmo]->Show();
		firearmUpgradeUIGroupMap[Firearm::Attribute::CriticalChance]->Show();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:
		break;

	}

}

void Shop::HideCurrentMenu() {

	switch (shopMenuIndex) {

	case ShopMenuIndex::Firearm:

		firearmUpgradeUIGroupMap[Firearm::Attribute::Damage]->Hide();
		firearmUpgradeUIGroupMap[Firearm::Attribute::ReloadTime]->Hide();
		firearmUpgradeUIGroupMap[Firearm::Attribute::MaxAmmo]->Hide();
		firearmUpgradeUIGroupMap[Firearm::Attribute::CriticalChance]->Hide();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:
		break;

	}

}

Shop::FirearmUpgrade::FirearmUpgrade(Firearm::Attribute initAttribute, function<bool(float, float)> initBetterNode) {

	name = "Upgrade";
	description = "Upgrade description";
	currentUpgrade = nullptr;
	tailNode = nullptr;
	attribute = initAttribute;
	betterNode = initBetterNode;

}

void Shop::FirearmUpgrade::AddUpgrade(Shop::UpgradeNode* newUpgrade) {

	if (!currentUpgrade) {

		currentUpgrade = newUpgrade;
		tailNode = newUpgrade;
		return;

	}

	if (!newUpgrade || !betterNode)
		throw new exception("Adding new upgrade worth less than previous one");

	tailNode->next = newUpgrade;
	tailNode = newUpgrade;

}

void Shop::FirearmUpgrade::UpgradeNext(Firearm* firearm) {

	if (!currentUpgrade || !firearm)
		return;

	UpgradeNode* nextUpgrade = currentUpgrade->next;

	firearm->ModifyAttributeMultiplier(attribute, currentUpgrade->amount);

	cout << "Upgrading to next tier. New amount: " << currentUpgrade->amount << " for " << currentUpgrade->cost << " cost" << endl;

	delete currentUpgrade;
	currentUpgrade = nextUpgrade;

}

void Shop::InitializeUI() {

	// Background
	background = new GameObject("Shop background", Layer::Menu);
	Image* background_image = background->AddComponent<Image>();
	background_image->LoadImage(BACKGROUND_PATH);
	background_image->showOnScreen = true;
	Transform* background_transform = background->GetComponent<Transform>();
	background_transform->position = Vector2::zero;
	background->Render = [background_image]() {
		background_image->Render();
		};

	// Firearm navigation button
	ButtonUIGroup* firearmButtonGroup = new ButtonUIGroup;
	firearmButtonGroup->image = new GameObject("Firearm image", Layer::Menu);
	Image* firearmButtonGroup_image = firearmButtonGroup->image->AddComponent<Image>();
	firearmButtonGroup_image->LoadImage(NAVIGATION_UNSELECTED_PATH);
	firearmButtonGroup_image->showOnScreen = true;
	firearmButtonGroup_image->transform->position = Math::SDLToC00(MENU_NAVIGATION_POSITION.at(ShopMenuIndex::Firearm), firearmButtonGroup_image->transform->scale);
	firearmButtonGroup->label = new GameObject("Firearm label", Layer::Menu);
	Text* firearmButtonGroup_text = firearmButtonGroup->label->AddComponent<Text>();
	firearmButtonGroup_text->LoadText(MENU_NAVIGATION_LABEL_MAP.at(ShopMenuIndex::Firearm), Color::WHITE, NAVIGATION_LABEL_SIZE);
	firearmButtonGroup_text->showOnScreen = true;
	firearmButtonGroup_text->transform->position = firearmButtonGroup_image->transform->position;
	firearmButtonGroup->button = new GameObject("Firearm button", Layer::Menu);
	Button* firearmButtonGroup_button = firearmButtonGroup->button->AddComponent<Button>();
	firearmButtonGroup_button->transform->scale = firearmButtonGroup_image->transform->scale;
	firearmButtonGroup_button->transform->position = firearmButtonGroup_image->transform->position;
	firearmButtonGroup_button->OnClick = [this]() {
		HideCurrentMenu();
		shopMenuIndex = ShopMenuIndex::Firearm;
		ShowCurrentMenu();
		};
	firearmButtonGroup->button->Render = [firearmButtonGroup_image, firearmButtonGroup_text]() {
		firearmButtonGroup_image->Render();
		firearmButtonGroup_text->Render();
		};
	menuNavigationButtonMap[ShopMenuIndex::Firearm] = firearmButtonGroup;

	// Melee navigation button
	ButtonUIGroup* meleeButtonGroup = new ButtonUIGroup;
	meleeButtonGroup->image = new GameObject("Melee image", Layer::Menu);
	Image* meleeButtonGroup_image = meleeButtonGroup->image->AddComponent<Image>();
	meleeButtonGroup_image->LoadImage(NAVIGATION_UNSELECTED_PATH);
	meleeButtonGroup_image->showOnScreen = true;
	meleeButtonGroup_image->transform->position = Math::SDLToC00(MENU_NAVIGATION_POSITION.at(ShopMenuIndex::Melee), meleeButtonGroup_image->transform->scale);
	meleeButtonGroup->label = new GameObject("Melee label", Layer::Menu);
	Text* meleeButtonGroup_text = meleeButtonGroup->label->AddComponent<Text>();
	meleeButtonGroup_text->LoadText(MENU_NAVIGATION_LABEL_MAP.at(ShopMenuIndex::Melee), Color::WHITE, NAVIGATION_LABEL_SIZE);
	meleeButtonGroup_text->showOnScreen = true;
	meleeButtonGroup_text->transform->position = meleeButtonGroup_image->transform->position;
	meleeButtonGroup->button = new GameObject("Melee button", Layer::Menu);
	Button* meleeButtonGroup_button = meleeButtonGroup->button->AddComponent<Button>();
	meleeButtonGroup_button->transform->scale = meleeButtonGroup_image->transform->scale;
	meleeButtonGroup_button->transform->position = meleeButtonGroup_image->transform->position;
	meleeButtonGroup_button->OnClick = [this]() {
		HideCurrentMenu();
		shopMenuIndex = ShopMenuIndex::Melee;
		ShowCurrentMenu();
		};
	meleeButtonGroup->button->Render = [meleeButtonGroup_image, meleeButtonGroup_text]() {
		meleeButtonGroup_image->Render();
		meleeButtonGroup_text->Render();
		};
	menuNavigationButtonMap[ShopMenuIndex::Melee] = meleeButtonGroup;

	// Utility navigation button
	ButtonUIGroup* utilityButtonGroup = new ButtonUIGroup;
	utilityButtonGroup->image = new GameObject("Utility image", Layer::Menu);
	Image* utilityButtonGroup_image = utilityButtonGroup->image->AddComponent<Image>();
	utilityButtonGroup_image->LoadImage(NAVIGATION_UNSELECTED_PATH);
	utilityButtonGroup_image->showOnScreen = true;
	utilityButtonGroup_image->transform->position = Math::SDLToC00(MENU_NAVIGATION_POSITION.at(ShopMenuIndex::Utility), utilityButtonGroup_image->transform->scale);
	utilityButtonGroup->label = new GameObject("Utility label", Layer::Menu);
	Text* utilityButtonGroup_text = utilityButtonGroup->label->AddComponent<Text>();
	utilityButtonGroup_text->LoadText(MENU_NAVIGATION_LABEL_MAP.at(ShopMenuIndex::Utility), Color::WHITE, NAVIGATION_LABEL_SIZE);
	utilityButtonGroup_text->showOnScreen = true;
	utilityButtonGroup_text->transform->position = utilityButtonGroup_image->transform->position;
	utilityButtonGroup->button = new GameObject("Utility button", Layer::Menu);
	Button* utilityButtonGroup_button = utilityButtonGroup->button->AddComponent<Button>();
	utilityButtonGroup_button->transform->scale = utilityButtonGroup_image->transform->scale;
	utilityButtonGroup_button->transform->position = utilityButtonGroup_image->transform->position;
	utilityButtonGroup_button->OnClick = [this]() {
		HideCurrentMenu();
		shopMenuIndex = ShopMenuIndex::Utility;
		ShowCurrentMenu();
		};
	utilityButtonGroup->button->Render = [utilityButtonGroup_image, utilityButtonGroup_text]() {
		utilityButtonGroup_image->Render();
		utilityButtonGroup_text->Render();
		};
	menuNavigationButtonMap[ShopMenuIndex::Utility] = utilityButtonGroup;

	// Damage upgrade
	FirearmUpgradeUIGroup* damageUpgradeUIGroup = new FirearmUpgradeUIGroup(this, Firearm::Attribute::Damage);
	damageUpgradeUIGroup->amount = firearmUpgradeMap[Firearm::Attribute::Damage]->NextUpgradeAmount();
	damageUpgradeUIGroup->cost = firearmUpgradeMap[Firearm::Attribute::Damage]->NextUpgradeCost();
	damageUpgradeUIGroup->descriptionPrefix = FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP.at(Firearm::Attribute::Damage);
	damageUpgradeUIGroup->descriptionSuffix = FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP.at(Firearm::Attribute::Damage);
	damageUpgradeUIGroup->label = FIREARM_UPGRADE_LABEL_MAP.at(Firearm::Attribute::Damage);
	damageUpgradeUIGroup->descriptionMargin = UPGRADE_DESCRIPTION_MARGIN;
	damageUpgradeUIGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	damageUpgradeUIGroup->Update(FIREARM_UPGRADE_POSITION.at(Firearm::Attribute::Damage));
	firearmUpgradeUIGroupMap[Firearm::Attribute::Damage] = damageUpgradeUIGroup;

	// Reload time upgrade
	FirearmUpgradeUIGroup* reloadTimeUpgradeUIGroup = new FirearmUpgradeUIGroup(this, Firearm::Attribute::ReloadTime);
	reloadTimeUpgradeUIGroup->amount = firearmUpgradeMap[Firearm::Attribute::ReloadTime]->NextUpgradeAmount();
	reloadTimeUpgradeUIGroup->cost = firearmUpgradeMap[Firearm::Attribute::ReloadTime]->NextUpgradeCost();
	reloadTimeUpgradeUIGroup->descriptionPrefix = FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP.at(Firearm::Attribute::ReloadTime);
	reloadTimeUpgradeUIGroup->descriptionSuffix = FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP.at(Firearm::Attribute::ReloadTime);
	reloadTimeUpgradeUIGroup->label = FIREARM_UPGRADE_LABEL_MAP.at(Firearm::Attribute::ReloadTime);
	reloadTimeUpgradeUIGroup->descriptionMargin = UPGRADE_DESCRIPTION_MARGIN;
	reloadTimeUpgradeUIGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	reloadTimeUpgradeUIGroup->Update(FIREARM_UPGRADE_POSITION.at(Firearm::Attribute::ReloadTime));
	firearmUpgradeUIGroupMap[Firearm::Attribute::ReloadTime] = reloadTimeUpgradeUIGroup;

	// Max ammo upgrade
	FirearmUpgradeUIGroup* maxAmmoUpgradeUIGroup = new FirearmUpgradeUIGroup(this, Firearm::Attribute::MaxAmmo);
	maxAmmoUpgradeUIGroup->amount = firearmUpgradeMap[Firearm::Attribute::MaxAmmo]->NextUpgradeAmount();
	maxAmmoUpgradeUIGroup->cost = firearmUpgradeMap[Firearm::Attribute::MaxAmmo]->NextUpgradeCost();
	maxAmmoUpgradeUIGroup->descriptionPrefix = FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP.at(Firearm::Attribute::MaxAmmo);
	maxAmmoUpgradeUIGroup->descriptionSuffix = FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP.at(Firearm::Attribute::MaxAmmo);
	maxAmmoUpgradeUIGroup->label = FIREARM_UPGRADE_LABEL_MAP.at(Firearm::Attribute::MaxAmmo);
	maxAmmoUpgradeUIGroup->descriptionMargin = UPGRADE_DESCRIPTION_MARGIN;
	maxAmmoUpgradeUIGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	maxAmmoUpgradeUIGroup->Update(FIREARM_UPGRADE_POSITION.at(Firearm::Attribute::MaxAmmo));
	firearmUpgradeUIGroupMap[Firearm::Attribute::MaxAmmo] = maxAmmoUpgradeUIGroup;

	// Critical chance upgrade
	FirearmUpgradeUIGroup* criticalChanceUpgradeUIGroup = new FirearmUpgradeUIGroup(this, Firearm::Attribute::CriticalChance);
	criticalChanceUpgradeUIGroup->amount = firearmUpgradeMap[Firearm::Attribute::CriticalChance]->NextUpgradeAmount();
	criticalChanceUpgradeUIGroup->cost = firearmUpgradeMap[Firearm::Attribute::CriticalChance]->NextUpgradeCost();
	criticalChanceUpgradeUIGroup->descriptionPrefix = FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP.at(Firearm::Attribute::CriticalChance);
	criticalChanceUpgradeUIGroup->descriptionSuffix = FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP.at(Firearm::Attribute::CriticalChance);
	criticalChanceUpgradeUIGroup->label = FIREARM_UPGRADE_LABEL_MAP.at(Firearm::Attribute::CriticalChance);
	criticalChanceUpgradeUIGroup->descriptionMargin = UPGRADE_DESCRIPTION_MARGIN;
	criticalChanceUpgradeUIGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	criticalChanceUpgradeUIGroup->Update(FIREARM_UPGRADE_POSITION.at(Firearm::Attribute::CriticalChance));
	firearmUpgradeUIGroupMap[Firearm::Attribute::CriticalChance] = criticalChanceUpgradeUIGroup;

	// -----------------------------------
	// FIREARM ATTRIBUTE INFO BOARD
	// -----------------------------------

	// -- General --
	firearmAttributeFrame = new GameObject("Firearm attribute frame", Layer::Menu);
	Image* firearmAttributeFrame_image = firearmAttributeFrame->AddComponent<Image>();
	firearmAttributeFrame_image->LoadImage(FIREARM_ATTRIBUTE_FRAME_PATH);
	firearmAttributeFrame_image->showOnScreen = true;
	firearmAttributeFrame->transform->position = Math::SDLToC00(FIREARM_ATTRIBUTE_FRAME_POSITION, firearmAttributeFrame->transform->scale);
	firearmAttributeFrame->Render = [firearmAttributeFrame_image]() {
		firearmAttributeFrame_image->Render();
		};

	// -- Damage --
	FirearmAttributeInfoGroup* damageInfoGroup = new FirearmAttributeInfoGroup;
	damageInfoGroup->label = FIREARM_ATTRIBUTE_LABEL_MAP.at(Firearm::Attribute::Damage);
	damageInfoGroup->amount = linkedPlayer->GetFirearm()->GetAttribute(Firearm::Attribute::Damage);
	damageInfoGroup->labelColor = Color::WHITE;
	damageInfoGroup->labelSize = FIREARM_ATTRIBUTE_LABEL_SIZE;
	damageInfoGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	damageInfoGroup->Update(FIREARM_ATTRIBUTE_POSITION_MAP.at(Firearm::Attribute::Damage), FIREARM_ATTRIBUTE_VALUE_LEFT);
	firearmAttributeInfoMap[Firearm::Attribute::Damage] = damageInfoGroup;

	// -- Reload time --
	FirearmAttributeInfoGroup* reloadTimeInfoGroup = new FirearmAttributeInfoGroup;
	reloadTimeInfoGroup->label = FIREARM_ATTRIBUTE_LABEL_MAP.at(Firearm::Attribute::ReloadTime);
	reloadTimeInfoGroup->amount = linkedPlayer->GetFirearm()->GetAttribute(Firearm::Attribute::ReloadTime);
	reloadTimeInfoGroup->labelColor = Color::WHITE;
	reloadTimeInfoGroup->labelSize = FIREARM_ATTRIBUTE_LABEL_SIZE;
	reloadTimeInfoGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	reloadTimeInfoGroup->Update(FIREARM_ATTRIBUTE_POSITION_MAP.at(Firearm::Attribute::ReloadTime), FIREARM_ATTRIBUTE_VALUE_LEFT);
	firearmAttributeInfoMap[Firearm::Attribute::ReloadTime] = reloadTimeInfoGroup;

	// -- Max ammo --
	FirearmAttributeInfoGroup* maxAmmoInfoGroup = new FirearmAttributeInfoGroup;
	maxAmmoInfoGroup->label = FIREARM_ATTRIBUTE_LABEL_MAP.at(Firearm::Attribute::MaxAmmo);
	maxAmmoInfoGroup->amount = linkedPlayer->GetFirearm()->GetAttribute(Firearm::Attribute::MaxAmmo);
	maxAmmoInfoGroup->labelColor = Color::WHITE;
	maxAmmoInfoGroup->labelSize = FIREARM_ATTRIBUTE_LABEL_SIZE;
	maxAmmoInfoGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	maxAmmoInfoGroup->Update(FIREARM_ATTRIBUTE_POSITION_MAP.at(Firearm::Attribute::MaxAmmo), FIREARM_ATTRIBUTE_VALUE_LEFT);
	firearmAttributeInfoMap[Firearm::Attribute::MaxAmmo] = maxAmmoInfoGroup;

	// -- Critical chance --
	FirearmAttributeInfoGroup* criticalChanceInfoGroup = new FirearmAttributeInfoGroup;
	criticalChanceInfoGroup->label = FIREARM_ATTRIBUTE_LABEL_MAP.at(Firearm::Attribute::CriticalChance);
	criticalChanceInfoGroup->amount = linkedPlayer->GetFirearm()->GetAttribute(Firearm::Attribute::CriticalChance);
	criticalChanceInfoGroup->labelColor = Color::WHITE;
	criticalChanceInfoGroup->labelSize = FIREARM_ATTRIBUTE_LABEL_SIZE;
	criticalChanceInfoGroup->amountDecimalPlace = FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	criticalChanceInfoGroup->Update(FIREARM_ATTRIBUTE_POSITION_MAP.at(Firearm::Attribute::CriticalChance), FIREARM_ATTRIBUTE_VALUE_LEFT);
	firearmAttributeInfoMap[Firearm::Attribute::CriticalChance] = criticalChanceInfoGroup;

}

void Shop::InitializeUpgrades() {

	// Reload time
	FirearmUpgrade* reloadTimeUpgrade = new FirearmUpgrade(
		Firearm::Attribute::ReloadTime,
		[](float newUp, float oldUp) { return newUp < oldUp; }
	);
	// NOT FUCKING MAGIC NUMBERS, JUST RANDOM BULLSHIT GO
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(10, 0.9f));
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(24, 0.8f));
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(45, 0.7f));
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(69, 0.65f));
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(124, 0.6f));
	reloadTimeUpgrade->AddUpgrade(new UpgradeNode(372, 0.4f));
	firearmUpgradeMap[Firearm::Attribute::ReloadTime] = reloadTimeUpgrade;



	// Damage
	FirearmUpgrade* damageUpgrade = new FirearmUpgrade(
		Firearm::Attribute::Damage
	);
	damageUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	damageUpgrade->AddUpgrade(new UpgradeNode(25, 1.5f));
	damageUpgrade->AddUpgrade(new UpgradeNode(64, 1.9f));
	damageUpgrade->AddUpgrade(new UpgradeNode(189, 2.3f));
	firearmUpgradeMap[Firearm::Attribute::Damage] = damageUpgrade;

	// Max ammo
	FirearmUpgrade* maxAmmoUpgrade = new FirearmUpgrade(
		Firearm::Attribute::MaxAmmo
	);
	maxAmmoUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	maxAmmoUpgrade->AddUpgrade(new UpgradeNode(54, 1.3f));
	maxAmmoUpgrade->AddUpgrade(new UpgradeNode(123, 1.5f));
	maxAmmoUpgrade->AddUpgrade(new UpgradeNode(256, 2.0f));
	firearmUpgradeMap[Firearm::Attribute::MaxAmmo] = maxAmmoUpgrade;

	// Critical chance
	FirearmUpgrade* criticalChanceUpgrade = new FirearmUpgrade(
		Firearm::Attribute::CriticalChance
	);
	criticalChanceUpgrade->AddUpgrade(new UpgradeNode(24, 0.3f));
	criticalChanceUpgrade->AddUpgrade(new UpgradeNode(74, 0.4f));
	criticalChanceUpgrade->AddUpgrade(new UpgradeNode(125, 0.55f));
	criticalChanceUpgrade->AddUpgrade(new UpgradeNode(299, 0.6f));
	criticalChanceUpgrade->AddUpgrade(new UpgradeNode(372, 0.7f));
	firearmUpgradeMap[Firearm::Attribute::CriticalChance] = criticalChanceUpgrade;

}

void Shop::BuyUpgrade(Firearm::Attribute attribute) {

	FirearmUpgrade* upgrade = firearmUpgradeMap[attribute];

	if (upgrade->NextUpgradeCost() >= 0 && GameManager::Instance()->TrySpendMoney(upgrade->NextUpgradeCost()))
		upgrade->UpgradeNext(linkedPlayer->GetFirearm());

	firearmAttributeInfoMap.at(attribute)->amount = linkedPlayer->GetFirearm()->GetAttribute(attribute);
	firearmAttributeInfoMap.at(attribute)->Update(FIREARM_ATTRIBUTE_POSITION_MAP.at(attribute), FIREARM_ATTRIBUTE_VALUE_LEFT);

}

int Shop::FirearmUpgrade::NextUpgradeCost() {

	if (currentUpgrade)
		return currentUpgrade->cost;

	return INT_MAX;

}

float Shop::FirearmUpgrade::NextUpgradeAmount() {

	if (currentUpgrade)
		return currentUpgrade->amount;

	return 0.0f;

}

FirearmAttributeInfoGroup::FirearmAttributeInfoGroup() {

	label = "Label";
	labelSize = 16;
	labelColor = Color::WHITE;
	amount = 0.0f;
	amountDecimalPlace = 0;

	labelObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* label_text = labelObject->AddComponent<Text>();
	label_text->showOnScreen = true;
	labelObject->Render = [label_text]() {
		label_text->Render();
		};
	amountLabelObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* amountLabel_text = amountLabelObject->AddComponent<Text>();
	amountLabel_text->showOnScreen = true;
	amountLabelObject->Render = [amountLabel_text]() {
		amountLabel_text->Render();
		};

}

void FirearmAttributeInfoGroup::Update(Vector2 labelPosition, float amountLabelLeft) {

	labelObject->name = label + OBJECT_NAME_SUFFIX;
	Text* label_text = labelObject->GetComponent<Text>();
	label_text->LoadText(label, labelColor, labelSize);
	label_text->transform->position = Math::SDLToC00(labelPosition, label_text->transform->scale);

	amountLabelObject->name = label + OBJECT_NAME_SUFFIX;
	Text* amountLabel_text = amountLabelObject->GetComponent<Text>();
	std::stringstream ss;
	ss << std::fixed << std::setprecision(amountDecimalPlace) << amount;
	std::string amountString = ss.str();
	amountLabel_text->LoadText(amountString, labelColor, labelSize);
	amountLabel_text->transform->position = Math::SDLToC00(
		Vector2(amountLabelLeft - amountLabel_text->transform->scale.x, labelPosition.y),
		amountLabel_text->transform->scale
	);

}

void FirearmAttributeInfoGroup::Show() {

	if (labelObject)
		labelObject->Enable();

	if (amountLabelObject)
		amountLabelObject->Enable();

}

void FirearmAttributeInfoGroup::Hide() {

	if (labelObject)
		labelObject->Disable();

	if (amountLabelObject)
		amountLabelObject->Disable();

}

FirearmUpgradeUIGroup::FirearmUpgradeUIGroup(Shop* initShop, Firearm::Attribute initAttribute) {

	if (!initShop)
		throw new exception("Updating node does not link to a shop object!");

	linkedShop = initShop;
	assignedAttribute = initAttribute;

	label = "Label";
	amount = 0.0f;
	descriptionMargin = 0.0f;
	cost = 0;
	amountDecimalPlace = 0;

	labelObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* label_text = labelObject->AddComponent<Text>();
	label_text->showOnScreen = true;
	labelObject->Render = [label_text]() {
		label_text->Render();
		};
	buttonObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Image* frame_image = buttonObject->AddComponent<Image>();
	frame_image->LoadImage(UPGRADE_SLOT_PATH);
	frame_image->showOnScreen = true;
	Button* button_button = buttonObject->AddComponent<Button>();
	button_button->backgroundColor = Color::TRANSPARENT;
	button_button->OnClick = [this]() {
		linkedShop->BuyUpgrade(assignedAttribute);
		};
	buttonObject->Render = [frame_image]() {
		frame_image->Render();
		};
	descriptionObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* description_text = descriptionObject->AddComponent<Text>();
	description_text->showOnScreen = true;
	description_text->wrapLength = buttonObject->transform->scale.x - 2.0f * descriptionMargin;
	descriptionObject->Render = [description_text]() {
		description_text->Render();
		};
	amountObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* amount_text = amountObject->AddComponent<Text>();
	amount_text->showOnScreen = true;
	amount_text->wrapLength = buttonObject->transform->scale.x - 2.0f * descriptionMargin;
	amountObject->Render = [amount_text]() {
		amount_text->Render();
		};
	costObject = new GameObject(label + OBJECT_NAME_SUFFIX, Layer::Menu);
	Text* cost_text = costObject->AddComponent<Text>();
	cost_text->showOnScreen = true;
	costObject->Render = [cost_text]() {
		cost_text->Render();
		};

}

void FirearmUpgradeUIGroup::Update(Vector2 framePosition) {

	// Frame
	buttonObject->transform->position = Math::SDLToC00(framePosition, buttonObject->transform->scale);

	// Label
	labelObject->name = label + OBJECT_NAME_SUFFIX;
	Text* label_text = labelObject->GetComponent<Text>();
	label_text->LoadText(label, UPGRADE_LABEL_COLOR, UPGRADE_LABEL_SIZE);
	label_text->transform->position = Vector2(
		buttonObject->transform->position.x,
		buttonObject->transform->position.y - (buttonObject->transform->scale - labelObject->transform->scale).y / 2.0f + UPGRADE_LABEL_OFFSET_Y
	);

	// Amount string
	std::stringstream ss;
	ss << std::fixed << std::setprecision(amountDecimalPlace) << amount;
	std::string amountString = ss.str();

	// Description label
	descriptionObject->name = label + OBJECT_NAME_SUFFIX;
	Text* description_text = descriptionObject->GetComponent<Text>();
	description_text->wrapLength = buttonObject->transform->scale.x - 2.0f * descriptionMargin;
	description_text->LoadText(descriptionPrefix + amountString + descriptionSuffix, UPGRADE_LABEL_COLOR, UPGRADE_DESCRIPTION_SIZE);
	description_text->transform->position = buttonObject->transform->position;

	// Description amount
	/*ss.str("");
	ss.clear();
	ss << std::setw(descriptionPrefix.size()) << std::setfill('a') << amountString;
	std::string amountStringSpan = ss.str();
	amountObject->name = label + OBJECT_NAME_SUFFIX;
	Text* amount_text = amountObject->GetComponent<Text>();
	amount_text->wrapLength = buttonObject->transform->scale.x - 2.0f * descriptionMargin;
	amount_text->LoadText(amountStringSpan, UPGRADE_ATTRIBUTE_COLOR, UPGRADE_DESCRIPTION_SIZE);
	amountObject->transform->position = Vector2(
		descriptionObject->transform->position.x,
		descriptionObject->transform->position.y - (descriptionObject->transform->scale - amountObject->transform->scale).y / 2.0f
	);*/

	// Cost
	costObject->name = label + OBJECT_NAME_SUFFIX;
	Text* cost_text = costObject->GetComponent<Text>();
	cost_text->LoadText(COST_PREFIX + std::to_string(cost), UPGRADE_LABEL_COLOR, UPGADE_COST_SIZE);
	cost_text->transform->position = Vector2(
		buttonObject->transform->position.x,
		buttonObject->transform->position.y - (buttonObject->transform->scale - labelObject->transform->scale).y / 2.0f + UPGRADE_COST_OFFSET_Y
	);

}

void FirearmUpgradeUIGroup::Show() {

	labelObject->Enable();
	buttonObject->Enable();
	descriptionObject->Enable();
	costObject->Enable();
	amountObject->Enable();

}

void FirearmUpgradeUIGroup::Hide() {

	labelObject->Disable();
	buttonObject->Disable();
	descriptionObject->Disable();
	costObject->Disable();
	amountObject->Disable();

}