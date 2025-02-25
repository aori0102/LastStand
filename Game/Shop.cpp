#include <Shop.h>
#include <Texture.h>
#include <Type.h>
#include <Game.h>
#include <Player.h>
#include <GameManager.h>

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

	InitializeUI();
	InitializeUpgrades();

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

	buyButton->Enable();
	buyButtonLabel->Enable();

	menuNavigationButtonMap.at(ShopMenuIndex::Firearm)->button->Enable();
	menuNavigationButtonMap.at(ShopMenuIndex::Melee)->button->Enable();
	menuNavigationButtonMap.at(ShopMenuIndex::Utility)->button->Enable();

}

void Shop::Hide() {

	background->Disable();

	buyButton->Disable();
	buyButtonLabel->Disable();

	menuNavigationButtonMap.at(ShopMenuIndex::Firearm)->button->Disable();
	menuNavigationButtonMap.at(ShopMenuIndex::Melee)->button->Disable();
	menuNavigationButtonMap.at(ShopMenuIndex::Utility)->button->Disable();

}

void Shop::RenderFirearmMenu() {

	damageUpgradeButton->GetComponent<Button>()->Render();
	damageUpgradeButtonLabel->GetComponent<Text>()->Render();
	damageUpgradeButtonAmountLabel->GetComponent<Text>()->Render();

	reloadTimeUpgradeButton->GetComponent<Button>()->Render();
	reloadTimeUpgradeButtonLabel->GetComponent<Text>()->Render();
	reloadTimeUpgradeButtonAmountLabel->GetComponent<Text>()->Render();

	ammoCapacityUpgradeButton->GetComponent<Button>()->Render();
	ammoCapacityUpgradeButtonLabel->GetComponent<Text>()->Render();
	ammoCapacityUpgradeButtonAmountLabel->GetComponent<Text>()->Render();

}

void Shop::ShowCurrentMenu() {

	switch (shopMenuIndex) {

	case ShopMenuIndex::Firearm:

		damageUpgradeButton->Enable();
		damageUpgradeButtonLabel->Enable();
		damageUpgradeButtonAmountLabel->Enable();

		reloadTimeUpgradeButton->Enable();
		reloadTimeUpgradeButtonLabel->Enable();
		reloadTimeUpgradeButtonAmountLabel->Enable();

		ammoCapacityUpgradeButton->Enable();
		ammoCapacityUpgradeButtonLabel->Enable();
		ammoCapacityUpgradeButtonAmountLabel->Enable();

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

		damageUpgradeButton->Disable();
		damageUpgradeButtonLabel->Disable();
		damageUpgradeButtonAmountLabel->Disable();

		reloadTimeUpgradeButton->Disable();
		reloadTimeUpgradeButtonLabel->Disable();
		reloadTimeUpgradeButtonAmountLabel->Disable();

		ammoCapacityUpgradeButton->Disable();
		ammoCapacityUpgradeButtonLabel->Disable();
		ammoCapacityUpgradeButtonAmountLabel->Disable();

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

	// Buy button
	buyButton = new GameObject("Buy button", Layer::Menu);
	Button* buyButton_button = buyButton->AddComponent<Button>();
	buyButton_button->backgroundColor = Color::WHITE;
	buyButton_button->OnClick = []() { cout << "Buy button is pressed" << endl; };
	Transform* buyButton_transform = buyButton->GetComponent<Transform>();
	buyButton_transform->scale = BUY_BUTTON_SIZE;
	buyButton_transform->position = Vector2(
		background_transform->position.x,
		background_transform->position.y + (background_transform->scale.y - BUY_BUTTON_SIZE.y) / 2.0f
	);
	buyButton->Render = [buyButton_button]() {
		buyButton_button->Render();
		};

	buyButtonLabel = new GameObject("Buy button label", Layer::Menu);
	Text* buyButtonLabel_text = buyButtonLabel->AddComponent<Text>();
	buyButtonLabel_text->LoadText("Buy", Color::BLUE, 24);
	buyButtonLabel_text->showOnScreen = true;
	Transform* buyButtonLabel_transform = buyButtonLabel->GetComponent<Transform>();
	buyButtonLabel_transform->position = buyButton_transform->position;
	buyButtonLabel->Render = [buyButtonLabel_text]() {
		buyButtonLabel_text->Render();
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
	damageUpgradeButton = new GameObject("Damage upgrade button", Layer::Menu);
	Button* damageUpgradeButton_button = damageUpgradeButton->AddComponent<Button>();
	damageUpgradeButton_button->backgroundColor = Color::WHITE;
	damageUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::Damage);
		};
	Transform* damageUpgradeButton_transform = damageUpgradeButton->GetComponent<Transform>();
	damageUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	damageUpgradeButton_transform->position = background_transform->position;
	damageUpgradeButton->Render = [damageUpgradeButton_button]() {
		damageUpgradeButton_button->Render();
		};

	damageUpgradeButtonLabel = new GameObject("Damage upgrade button label", Layer::Menu);
	Text* damageUpgradeButtonLabel_text = damageUpgradeButtonLabel->AddComponent<Text>();
	damageUpgradeButtonLabel_text->LoadText("Damage upgrade", Color::BLUE, 24);
	damageUpgradeButtonLabel_text->showOnScreen = true;
	Transform* damageUpgradeButtonLabel_transform = damageUpgradeButtonLabel->GetComponent<Transform>();
	damageUpgradeButtonLabel_transform->position = damageUpgradeButton_transform->position;
	damageUpgradeButtonLabel->Render = [damageUpgradeButtonLabel_text]() {
		damageUpgradeButtonLabel_text->Render();
		};

	damageUpgradeButtonAmountLabel = new GameObject("Damage upgrade button amount label", Layer::Menu);
	Text* damageUpgradeButtonAmountLabel_text = damageUpgradeButtonAmountLabel->AddComponent<Text>();
	damageUpgradeButtonAmountLabel_text->LoadText("Damage upgrade", Color::BLUE, 24);
	damageUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* damageUpgradeButtonAmountLabel_transform = damageUpgradeButtonAmountLabel->GetComponent<Transform>();
	damageUpgradeButtonAmountLabel_transform->position = damageUpgradeButton_transform->position;
	damageUpgradeButtonAmountLabel->Render = [damageUpgradeButtonAmountLabel_text]() {
		damageUpgradeButtonAmountLabel_text->Render();
		};

	// Reload time upgrade
	reloadTimeUpgradeButton = new GameObject("Reload time upgrade button", Layer::Menu);
	Button* reloadTimeUpgradeButton_button = reloadTimeUpgradeButton->AddComponent<Button>();
	reloadTimeUpgradeButton_button->backgroundColor = Color::WHITE;
	reloadTimeUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::ReloadTime);
		};
	Transform* reloadTimeUpgradeButton_transform = reloadTimeUpgradeButton->GetComponent<Transform>();
	reloadTimeUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	reloadTimeUpgradeButton_transform->position =
		damageUpgradeButton_transform->position + Vector2::up * (UPGRADE_VERTICAL_MARGIN + UPGRADE_BUTTON_SIZE.y);
	reloadTimeUpgradeButton->Render = [reloadTimeUpgradeButton_button]() {
		reloadTimeUpgradeButton_button->Render();
		};

	reloadTimeUpgradeButtonLabel = new GameObject("Reload time upgrade button label", Layer::Menu);
	Text* reloadTimeUpgradeButtonLabel_text = reloadTimeUpgradeButtonLabel->AddComponent<Text>();
	reloadTimeUpgradeButtonLabel_text->LoadText("Reload time upgrade", Color::BLUE, 24);
	reloadTimeUpgradeButtonLabel_text->showOnScreen = true;
	Transform* reloadTimeUpgradeButtonLabel_transform = reloadTimeUpgradeButtonLabel->GetComponent<Transform>();
	reloadTimeUpgradeButtonLabel_transform->position = reloadTimeUpgradeButton_transform->position;
	reloadTimeUpgradeButtonLabel->Render = [reloadTimeUpgradeButtonLabel_text]() {
		reloadTimeUpgradeButtonLabel_text->Render();
		};

	reloadTimeUpgradeButtonAmountLabel = new GameObject("Reload time upgrade button amount label", Layer::Menu);
	Text* reloadTimeUpgradeButtonAmountLabel_text = reloadTimeUpgradeButtonAmountLabel->AddComponent<Text>();
	reloadTimeUpgradeButtonAmountLabel_text->LoadText("Reload time upgrade", Color::BLUE, 24);
	reloadTimeUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* reloadTimeUpgradeButtonAmountLabel_transform = reloadTimeUpgradeButtonAmountLabel->GetComponent<Transform>();
	reloadTimeUpgradeButtonAmountLabel_transform->position = reloadTimeUpgradeButton_transform->position;
	reloadTimeUpgradeButtonAmountLabel->Render = [reloadTimeUpgradeButtonAmountLabel_text]() {
		reloadTimeUpgradeButtonAmountLabel_text->Render();
		};

	// Ammo capacity upgrade
	ammoCapacityUpgradeButton = new GameObject("Ammo capacity upgrade button", Layer::Menu);
	Button* ammoCapacityUpgradeButton_button = ammoCapacityUpgradeButton->AddComponent<Button>();
	ammoCapacityUpgradeButton_button->backgroundColor = Color::WHITE;
	ammoCapacityUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::AmmoCapacity);
		};
	Transform* ammoCapacityUpgradeButton_transform = ammoCapacityUpgradeButton->GetComponent<Transform>();
	ammoCapacityUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	ammoCapacityUpgradeButton_transform->position =
		damageUpgradeButton_transform->position + Vector2::down * (UPGRADE_VERTICAL_MARGIN + UPGRADE_BUTTON_SIZE.y);
	ammoCapacityUpgradeButton->Render = [ammoCapacityUpgradeButton_button]() {
		ammoCapacityUpgradeButton_button->Render();
		};

	ammoCapacityUpgradeButtonLabel = new GameObject("Ammo capacity upgrade button label", Layer::Menu);
	Text* ammoCapacityUpgradeButtonLabel_text = ammoCapacityUpgradeButtonLabel->AddComponent<Text>();
	ammoCapacityUpgradeButtonLabel_text->LoadText("Ammo capacity upgrade", Color::BLUE, 24);
	ammoCapacityUpgradeButtonLabel_text->showOnScreen = true;
	Transform* ammoCapacityUpgradeButtonLabel_transform = ammoCapacityUpgradeButtonLabel->GetComponent<Transform>();
	ammoCapacityUpgradeButtonLabel_transform->position = ammoCapacityUpgradeButton_transform->position;
	ammoCapacityUpgradeButtonLabel->Render = [ammoCapacityUpgradeButtonLabel_text]() {
		ammoCapacityUpgradeButtonLabel_text->Render();
		};

	ammoCapacityUpgradeButtonAmountLabel = new GameObject("Ammo capacity upgrade button amount label", Layer::Menu);
	Text* ammoCapacityUpgradeButtonAmountLabel_text = ammoCapacityUpgradeButtonAmountLabel->AddComponent<Text>();
	ammoCapacityUpgradeButtonAmountLabel_text->LoadText("Ammo capacity upgrade", Color::BLUE, 24);
	ammoCapacityUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* ammoCapacityUpgradeButtonAmountLabel_transform = ammoCapacityUpgradeButtonAmountLabel->GetComponent<Transform>();
	ammoCapacityUpgradeButtonAmountLabel_transform->position = ammoCapacityUpgradeButton_transform->position;
	ammoCapacityUpgradeButtonAmountLabel->Render = [ammoCapacityUpgradeButtonAmountLabel_text]() {
		ammoCapacityUpgradeButtonAmountLabel_text->Render();
		};

}

void Shop::InitializeUpgrades() {

	// Reload time
	FirearmUpgrade* reloadTimeUpgrade = new FirearmUpgrade(
		Firearm::Attribute::ReloadTime,
		[](float newUp, float oldUp) { return newUp < oldUp; }
	);
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

	// Ammo capacity        
	FirearmUpgrade* ammoCapacityUpgrade = new FirearmUpgrade(
		Firearm::Attribute::AmmoCapacity
	);
	ammoCapacityUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	ammoCapacityUpgrade->AddUpgrade(new UpgradeNode(54, 1.3f));
	ammoCapacityUpgrade->AddUpgrade(new UpgradeNode(123, 1.5f));
	ammoCapacityUpgrade->AddUpgrade(new UpgradeNode(256, 2.0f));
	firearmUpgradeMap[Firearm::Attribute::AmmoCapacity] = ammoCapacityUpgrade;

}

void Shop::BuyUpgrade(Firearm::Attribute attribute) {

	FirearmUpgrade* upgrade = firearmUpgradeMap[attribute];

	if (upgrade->NextUpgradeCost() >= 0 && GameManager::Instance()->TrySpendMoney(upgrade->NextUpgradeCost()))
		upgrade->UpgradeNext(linkedPlayer->GetFirearm());

}

int Shop::FirearmUpgrade::NextUpgradeCost() {

	if (currentUpgrade)
		return currentUpgrade->cost;

	return -1;

}