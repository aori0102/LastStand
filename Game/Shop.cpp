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

		if (shopMenuIndex == ShopMenuIndex::Firearm)
			ShowFirearmMenu();

	} else {

		linkedPlayer->EnableInteraction();
		Hide();

		HideFirearmMenu();

	}

}

void Shop::Show() {

	buyButton->Enable();

	firearmButton->Enable();

	meleeButton->Enable();

	utilityButton->Enable();

}

void Shop::Hide() {

	buyButton->Disable();

	firearmButton->Disable();

	meleeButton->Disable();

	utilityButton->Disable();

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

void Shop::ShowFirearmMenu() {

	damageUpgradeButton->GetComponent<Button>()->Enable();
	reloadTimeUpgradeButton->GetComponent<Button>()->Enable();
	ammoCapacityUpgradeButton->GetComponent<Button>()->Enable();

}

void Shop::HideFirearmMenu() {

	damageUpgradeButton->GetComponent<Button>()->Disable();
	reloadTimeUpgradeButton->GetComponent<Button>()->Disable();
	ammoCapacityUpgradeButton->GetComponent<Button>()->Disable();

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
	background->AddComponent<Image>()->backgroundColor = Color(0, 0, 0, 100);
	Transform* background_transform = background->GetComponent<Transform>();
	background_transform->position = Game::WindowResolution() / 2.0f;
	background_transform->scale = SHOP_BACKGROUND_SIZE;

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

	buyButtonLabel = new GameObject("Buy button label", Layer::Menu);
	Text* buyButtonLabel_text = buyButtonLabel->AddComponent<Text>();
	buyButtonLabel_text->LoadText("Buy", Color::BLUE, 24);
	buyButtonLabel_text->showOnScreen = true;
	Transform* buyButtonLabel_transform = buyButtonLabel->GetComponent<Transform>();
	buyButtonLabel_transform->position = buyButton_transform->position;

	// Firearm navigation button
	firearmButton = new GameObject("Firearm button", Layer::Menu);
	Button* firearmButton_button = firearmButton->AddComponent<Button>();
	firearmButton_button->backgroundColor = Color::WHITE;
	firearmButton_button->OnClick = []() {cout << "Firearm button is pressed" << endl; };
	Transform* firearmButton_transform = firearmButton->GetComponent<Transform>();
	firearmButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	firearmButton_transform->position = Vector2(
		background_transform->position.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	firearmButtonLabel = new GameObject("Firearm button label", Layer::Menu);
	Text* firearmButtonLabel_text = firearmButtonLabel->AddComponent<Text>();
	firearmButtonLabel_text->LoadText("Firearm", Color::BLUE, 24);
	firearmButtonLabel_text->showOnScreen = true;
	Transform* firearmButtonLabel_transform = firearmButtonLabel->GetComponent<Transform>();
	firearmButtonLabel_transform->position = firearmButton_transform->position;

	// Melee navigation button
	meleeButton = new GameObject("Melee button", Layer::Menu);
	Button* meleeButton_button = meleeButton->AddComponent<Button>();
	meleeButton_button->backgroundColor = Color::WHITE;
	meleeButton_button->OnClick = []() {cout << "Melee button is pressed" << endl; };
	Transform* meleeButton_transform = meleeButton->GetComponent<Transform>();
	meleeButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	meleeButton_transform->position = Vector2(
		firearmButton_transform->position.x - (firearmButton_transform->scale.x + meleeButton_transform->scale.x) / 2.0f - NAVIGATION_BUTTON_OFFSET.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	meleeButtonLabel = new GameObject("Melee button label", Layer::Menu);
	Text* meleeButtonLabel_text = meleeButtonLabel->AddComponent<Text>();
	meleeButtonLabel_text->LoadText("Melee", Color::BLUE, 24);
	meleeButtonLabel_text->showOnScreen = true;
	Transform* meleeButtonLabel_transform = meleeButtonLabel->GetComponent<Transform>();
	meleeButtonLabel_transform->position = meleeButton_transform->position;

	// Utility navigation button
	utilityButton = new GameObject("Utility button", Layer::Menu);
	Button* utilityButton_button = utilityButton->AddComponent<Button>();
	utilityButton_button->backgroundColor = Color::WHITE;
	utilityButton_button->OnClick = []() {cout << "Utility button is pressed" << endl; };
	Transform* utilityButton_transform = utilityButton->GetComponent<Transform>();
	utilityButton_transform->scale = NAVIGATION_BUTTON_SIZE;
	utilityButton_transform->position = Vector2(
		firearmButton_transform->position.x + (firearmButton_transform->scale.x + utilityButton_transform->scale.x) / 2.0f + NAVIGATION_BUTTON_OFFSET.x,
		background_transform->position.y - (background_transform->scale.y - NAVIGATION_BUTTON_SIZE.y) / 2.0f + NAVIGATION_BUTTON_OFFSET.y
	);

	utilityButtonLabel = new GameObject("Utility button label", Layer::Menu);
	Text* utilityButtonLabel_text = utilityButtonLabel->AddComponent<Text>();
	utilityButtonLabel_text->LoadText("Utility", Color::BLUE, 24);
	utilityButtonLabel_text->showOnScreen = true;
	Transform* utilityButtonLabel_transform = utilityButtonLabel->GetComponent<Transform>();
	utilityButtonLabel_transform->position = utilityButton_transform->position;

	// Damage upgrade
	damageUpgradeButton = new GameObject("Damage upgrade button", Layer::Menu);
	Button* damageUpgradeButton_button = damageUpgradeButton->AddComponent<Button>();
	damageUpgradeButton_button->backgroundColor = Color::WHITE;
	damageUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::Damage);
		};
	Transform* damageUpgradeButton_transform = damageUpgradeButton->GetComponent<Transform>();
	damageUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	damageUpgradeButton_transform->position = Vector2(
		background_transform->position.x,
		UPGRADE_BUTTON_TOP
	);

	damageUpgradeButtonLabel = new GameObject("Damage upgrade button label", Layer::Menu);
	Text* damageUpgradeButtonLabel_text = damageUpgradeButtonLabel->AddComponent<Text>();
	damageUpgradeButtonLabel_text->LoadText("Damage upgrade", Color::BLUE, 24);
	damageUpgradeButtonLabel_text->showOnScreen = true;
	Transform* damageUpgradeButtonLabel_transform = damageUpgradeButtonLabel->GetComponent<Transform>();
	damageUpgradeButtonLabel_transform->position = damageUpgradeButton_transform->position;

	damageUpgradeButtonAmountLabel = new GameObject("Damage upgrade button amount label", Layer::Menu);
	Text* damageUpgradeButtonAmountLabel_text = damageUpgradeButtonAmountLabel->AddComponent<Text>();
	damageUpgradeButtonAmountLabel_text->LoadText("Damage upgrade", Color::BLUE, 24);
	damageUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* damageUpgradeButtonAmountLabel_transform = damageUpgradeButtonAmountLabel->GetComponent<Transform>();
	damageUpgradeButtonAmountLabel_transform->position = damageUpgradeButton_transform->position;

	// Reload time upgrade
	reloadTimeUpgradeButton = new GameObject("Reload time upgrade button", Layer::Menu);
	Button* reloadTimeUpgradeButton_button = reloadTimeUpgradeButton->AddComponent<Button>();
	reloadTimeUpgradeButton_button->backgroundColor = Color::WHITE;
	reloadTimeUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::ReloadTime);
		};
	Transform* reloadTimeUpgradeButton_transform = reloadTimeUpgradeButton->GetComponent<Transform>();
	reloadTimeUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	reloadTimeUpgradeButton_transform->position = Vector2(
		background_transform->position.x,
		damageUpgradeButton_transform->position.y + (damageUpgradeButton_transform->scale + reloadTimeUpgradeButton_transform->scale).y / 2.0f + UPGRADE_BUTTON_VERTICAL_OFFSET
	);

	reloadTimeUpgradeButtonLabel = new GameObject("Reload time upgrade button label", Layer::Menu);
	Text* reloadTimeUpgradeButtonLabel_text = reloadTimeUpgradeButtonLabel->AddComponent<Text>();
	reloadTimeUpgradeButtonLabel_text->LoadText("Reload time upgrade", Color::BLUE, 24);
	reloadTimeUpgradeButtonLabel_text->showOnScreen = true;
	Transform* reloadTimeUpgradeButtonLabel_transform = reloadTimeUpgradeButtonLabel->GetComponent<Transform>();
	reloadTimeUpgradeButtonLabel_transform->position = reloadTimeUpgradeButton_transform->position;

	reloadTimeUpgradeButtonAmountLabel = new GameObject("Reload time upgrade button amount label", Layer::Menu);
	Text* reloadTimeUpgradeButtonAmountLabel_text = reloadTimeUpgradeButtonAmountLabel->AddComponent<Text>();
	reloadTimeUpgradeButtonAmountLabel_text->LoadText("Reload time upgrade", Color::BLUE, 24);
	reloadTimeUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* reloadTimeUpgradeButtonAmountLabel_transform = reloadTimeUpgradeButtonAmountLabel->GetComponent<Transform>();
	reloadTimeUpgradeButtonAmountLabel_transform->position = reloadTimeUpgradeButton_transform->position;

	// Ammo capacity upgrade
	ammoCapacityUpgradeButton = new GameObject("Ammo capacity upgrade button", Layer::Menu);
	Button* ammoCapacityUpgradeButton_button = ammoCapacityUpgradeButton->AddComponent<Button>();
	ammoCapacityUpgradeButton_button->backgroundColor = Color::WHITE;
	ammoCapacityUpgradeButton_button->OnClick = [this]() {
		BuyUpgrade(Firearm::Attribute::AmmoCapacity);
		};
	Transform* ammoCapacityUpgradeButton_transform = ammoCapacityUpgradeButton->GetComponent<Transform>();
	ammoCapacityUpgradeButton_transform->scale = UPGRADE_BUTTON_SIZE;
	ammoCapacityUpgradeButton_transform->position = Vector2(
		background_transform->position.x,
		reloadTimeUpgradeButton_transform->position.y + (reloadTimeUpgradeButton_transform->scale + ammoCapacityUpgradeButton_transform->scale).y / 2.0f + UPGRADE_BUTTON_VERTICAL_OFFSET
	);

	ammoCapacityUpgradeButtonLabel = new GameObject("Ammo capacity upgrade button label", Layer::Menu);
	Text* ammoCapacityUpgradeButtonLabel_text = ammoCapacityUpgradeButtonLabel->AddComponent<Text>();
	ammoCapacityUpgradeButtonLabel_text->LoadText("Ammo capacity upgrade", Color::BLUE, 24);
	ammoCapacityUpgradeButtonLabel_text->showOnScreen = true;
	Transform* ammoCapacityUpgradeButtonLabel_transform = ammoCapacityUpgradeButtonLabel->GetComponent<Transform>();
	ammoCapacityUpgradeButtonLabel_transform->position = ammoCapacityUpgradeButton_transform->position;

	ammoCapacityUpgradeButtonAmountLabel = new GameObject("Ammo capacity upgrade button amount label", Layer::Menu);
	Text* ammoCapacityUpgradeButtonAmountLabel_text = ammoCapacityUpgradeButtonAmountLabel->AddComponent<Text>();
	ammoCapacityUpgradeButtonAmountLabel_text->LoadText("Ammo capacity upgrade", Color::BLUE, 24);
	ammoCapacityUpgradeButtonAmountLabel_text->showOnScreen = true;
	Transform* ammoCapacityUpgradeButtonAmountLabel_transform = ammoCapacityUpgradeButtonAmountLabel->GetComponent<Transform>();
	ammoCapacityUpgradeButtonAmountLabel_transform->position = ammoCapacityUpgradeButton_transform->position;

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