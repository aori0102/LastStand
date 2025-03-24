/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Shop.h>

#include <iomanip>
#include <sstream>
#include <string>

#include <Firearm.h>
#include <FirearmAttributeUIGroup.h>
#include <FirearmSelectionUI.h>
#include <FirearmUpgrade.h>
#include <FirearmUpgradeUIGroup.h>
#include <GameCore.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <Texture.h>
#include <Type.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

Shop* Shop::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Shop::Show() {

	uiElementMap.at(UIElementIndex::Shop_Background)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Melee)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Utility)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm_Label)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Melee_Label)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Utility_Label)->Enable();

	ShowCurrentMenu();

}

void Shop::Hide() {

	for (auto it = uiElementMap.begin(); it != uiElementMap.end(); it++)
		(it->second)->Disable();

}

void Shop::ShowCurrentMenu() {

	switch (currentMenuIndex) {

	case ShopMenuIndex::Firearm_Main:

		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Damage)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Firerate)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->Enable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Content)->Enable();

		break;

	case ShopMenuIndex::Firearm_Selection:

		uiElementMap.at(UIElementIndex::Firearm_Selection_Grid)->Enable();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:
		break;

	}

}

void Shop::HideCurrentMenu() {

	switch (currentMenuIndex) {

	case ShopMenuIndex::Firearm_Main:

		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Damage)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Firerate)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->Disable();
		uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Content)->Disable();

		break;

	case ShopMenuIndex::Firearm_Selection:

		uiElementMap.at(UIElementIndex::Firearm_Selection_Grid)->Disable();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:
		break;

	}

}

void Shop::InitializeUI() {
	/// >>>
	/// --- BACKGROUND ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Background] = new GameObject("Shop Background", Layer::Menu);
	Image* background_image = uiElementMap.at(UIElementIndex::Shop_Background)->AddComponent<Image>();
	background_image->showOnScreen = true;
	background_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_Background), true);
	background_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Background),
		background_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Shop_Background)->Render = [background_image]() {
		background_image->Render();
		};

	/// >>>
	/// --- FIREARM NAVIGATION ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Firearm] = new GameObject("Navigation Firearm", Layer::Menu);
	Image* navigationFirearm_image = uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm)->AddComponent<Image>();
	navigationFirearm_image->showOnScreen = true;
	navigationFirearm_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationFirearm_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Firearm),
		navigationFirearm_image->transform->scale
	);
	Button* navigationFirearm_button = uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm)->AddComponent<Button>();
	navigationFirearm_button->backgroundColor = Color::WHITE;
	navigationFirearm_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Firearm_Main);
		};
	uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm)->Render = [navigationFirearm_image]() {
		navigationFirearm_image->Render();
		};

	/// >>>
	/// --- FIREARM NAVIGATION LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Firearm_Label] = new GameObject("Navigation Firearm Label", Layer::Menu);
	Text* navigationFirearmLabel_text = uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm_Label)->AddComponent<Text>();
	navigationFirearmLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Firearm_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Firearm_Label)
	);
	navigationFirearmLabel_text->showOnScreen = true;
	navigationFirearmLabel_text->transform->position = navigationFirearm_image->transform->position;
	uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm_Label)->Render = [navigationFirearmLabel_text]() {
		navigationFirearmLabel_text->Render();
		};

	/// >>>
	/// --- MELEE NAVIGATION ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Melee] = new GameObject("Navigation Melee", Layer::Menu);
	Image* navigationMelee_image = uiElementMap.at(UIElementIndex::Shop_Navigation_Melee)->AddComponent<Image>();
	navigationMelee_image->showOnScreen = true;
	navigationMelee_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationMelee_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Melee),
		navigationMelee_image->transform->scale
	);
	Button* navigationMelee_button = uiElementMap.at(UIElementIndex::Shop_Navigation_Melee)->AddComponent<Button>();
	navigationMelee_button->backgroundColor = Color::WHITE;
	navigationMelee_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Melee);
		};
	uiElementMap.at(UIElementIndex::Shop_Navigation_Melee)->Render = [navigationMelee_image]() {
		navigationMelee_image->Render();
		};

	/// >>>
	/// --- MELEE NAVIGATION LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Melee_Label] = new GameObject("Navigation Melee Label", Layer::Menu);
	Text* navigationMeleeLabel_text = uiElementMap.at(UIElementIndex::Shop_Navigation_Melee_Label)->AddComponent<Text>();
	navigationMeleeLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Melee_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Melee_Label)
	);
	navigationMeleeLabel_text->showOnScreen = true;
	navigationMeleeLabel_text->transform->position = navigationMelee_image->transform->position;
	uiElementMap.at(UIElementIndex::Shop_Navigation_Melee_Label)->Render = [navigationMeleeLabel_text]() {
		navigationMeleeLabel_text->Render();
		};

	/// >>>
	/// --- UTILITY NAVIGATION ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Utility] = new GameObject("Navigation Utility", Layer::Menu);
	Image* navigationUtility_image = uiElementMap.at(UIElementIndex::Shop_Navigation_Utility)->AddComponent<Image>();
	navigationUtility_image->showOnScreen = true;
	navigationUtility_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationUtility_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Utility),
		navigationUtility_image->transform->scale
	);
	Button* navigationUtility_button = uiElementMap.at(UIElementIndex::Shop_Navigation_Utility)->AddComponent<Button>();
	navigationUtility_button->backgroundColor = Color::WHITE;
	navigationUtility_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Utility);
		};
	uiElementMap.at(UIElementIndex::Shop_Navigation_Utility)->Render = [navigationUtility_image]() {
		navigationUtility_image->Render();
		};

	/// >>>
	/// --- UTILITY NAVIGATION LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Shop_Navigation_Utility_Label] = new GameObject("Navigation Utility Label", Layer::Menu);
	Text* navigationUtilityLabel_text = uiElementMap.at(UIElementIndex::Shop_Navigation_Utility_Label)->AddComponent<Text>();
	navigationUtilityLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Utility_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Utility_Label)
	);
	navigationUtilityLabel_text->showOnScreen = true;
	navigationUtilityLabel_text->transform->position = navigationUtility_image->transform->position;
	uiElementMap.at(UIElementIndex::Shop_Navigation_Utility_Label)->Render = [navigationUtilityLabel_text]() {
		navigationUtilityLabel_text->Render();
		};

	/// >>>
	/// --- DAMAGE UPGRADE ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_Damage] = new FirearmUpgradeUIGroup("Damage", FirearmAttributeIndex::Damage);
	FirearmUpgradeUIGroup* upgradeDamageUIGroup = uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Damage)->As<FirearmUpgradeUIGroup>();
	upgradeDamageUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::Damage)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeDamageUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::Damage)->NextUpgradeCost());
	upgradeDamageUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));

	/// >>>
	/// --- CRITICAL DAMAGE UPGRADE ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_CriticalDamage] = new FirearmUpgradeUIGroup("Critical Damage", FirearmAttributeIndex::CriticalDamage);
	FirearmUpgradeUIGroup* upgradeCriticalDamageUIGroup = uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage)->As<FirearmUpgradeUIGroup>();
	upgradeCriticalDamageUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::CriticalDamage)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeCriticalDamageUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::CriticalDamage)->NextUpgradeCost());
	upgradeCriticalDamageUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));

	/// >>>
	/// --- FIRERATE UPGRADE ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_Firerate] = new FirearmUpgradeUIGroup("Firerate", FirearmAttributeIndex::Firerate);
	FirearmUpgradeUIGroup* upgradeFirerateUIGroup = uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_Firerate)->As<FirearmUpgradeUIGroup>();
	upgradeFirerateUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::Firerate)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeFirerateUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::Firerate)->NextUpgradeCost());
	upgradeFirerateUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));

	/// >>>
	/// --- MAGAZINE CAPACITY UPGRADE ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity] = new FirearmUpgradeUIGroup("Magazine capacity", FirearmAttributeIndex::MagazineCapacity);
	FirearmUpgradeUIGroup* upgradeMagazineCapacityUIGroup = uiElementMap.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity)->As<FirearmUpgradeUIGroup>();
	upgradeMagazineCapacityUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::MagazineCapacity)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeMagazineCapacityUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::MagazineCapacity)->NextUpgradeCost());
	upgradeMagazineCapacityUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));

	/// >>>
	/// --- FIREARM VIEWPORT ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_GunViewport] = new GameObject("Firearm Viewport", Layer::Menu);
	Image* firearmViewport_image = uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->AddComponent<Image>();
	firearmViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_GunViewport), true);
	firearmViewport_image->showOnScreen = true;
	firearmViewport_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_GunViewport),
		firearmViewport_image->transform->scale
	);
	Button* firearmViewport_button = uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->AddComponent<Button>();
	firearmViewport_button->backgroundColor = Color::TRANSPARENT;
	firearmViewport_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Firearm_Selection);
		};
	uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->Render = [firearmViewport_image]() {
		firearmViewport_image->Render();
		};

	/// >>>
	/// --- FIREARM VIEWPORT VISUAL ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_GunViewportVisual] = new GameObject("Firearm Viewport Visual", Layer::Menu);
	Image* firearmViewportVisual_image = uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->AddComponent<Image>();
	firearmViewportVisual_image->showOnScreen = true;
	firearmViewportVisual_image->transform->position = firearmViewport_image->transform->position;
	uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->Render = [firearmViewportVisual_image]() {
		firearmViewportVisual_image->Render();
		};

	/// >>>
	/// --- FIREARM LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_GunLabel] = new GameObject("Firearm Label", Layer::Menu);
	Text* firearmLabel_text = uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->AddComponent<Text>();
	firearmLabel_text->LoadText("<Gun Label>", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Firearm_Main_GunLabel));
	firearmLabel_text->showOnScreen = true;
	firearmLabel_text->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_GunLabel),
		UI_ELEMENT_SCALE_MAP.at(UIElementIndex::Firearm_Main_GunLabel)
	);
	uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->Render = [firearmLabel_text]() {
		firearmLabel_text->Render();
		};

	/// >>>
	/// --- FIREARM SELECTION GRID ---
	/// >>>
	FirearmSelectionUI* firearmSelectionUI = new FirearmSelectionUI;
	firearmSelectionUI->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Selection_Grid));
	std::vector<Firearm*> firearmList = Player::Instance()->GetFirearmList();
	for (Firearm* firearm : firearmList)
		firearmSelectionUI->AddFirearm(firearm);
	uiElementMap[UIElementIndex::Firearm_Selection_Grid] = firearmSelectionUI;

	/// >>>
	/// --- ATTRIBUTE FRAME ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Frame] = new GameObject("Attribute frame", Layer::Menu);
	Image* firearmAttributeFrame_image = uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->AddComponent<Image>();
	firearmAttributeFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_AttributeFrame), true);
	firearmAttributeFrame_image->showOnScreen = true;
	firearmAttributeFrame_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Frame),
		firearmAttributeFrame_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->Render = [firearmAttributeFrame_image]() {
		firearmAttributeFrame_image->Render();
		};

	/// >>>
	/// --- ATTRIBUTE FRAME --- 
	/// >>>
	FirearmAttributeUIGroup* attributeUIGroup = new FirearmAttributeUIGroup;
	attributeUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Content));
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Content] = attributeUIGroup;

}

void Shop::InitializeUpgrades() {

	// Reload time
	FirearmUpgrade* firerateUpgrade = new FirearmUpgrade(
		FirearmAttributeIndex::Firerate
	);
	// NOT FUCKING MAGIC NUMBERS, JUST RANDOM BULLSHIT GO
	firerateUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	firerateUpgrade->AddUpgrade(new UpgradeNode(24, 1.3f));
	firerateUpgrade->AddUpgrade(new UpgradeNode(45, 1.4f));
	firerateUpgrade->AddUpgrade(new UpgradeNode(69, 1.5f));
	firerateUpgrade->AddUpgrade(new UpgradeNode(124, 1.6f));
	firerateUpgrade->AddUpgrade(new UpgradeNode(372, 1.7f));
	firearmUpgradeMap[FirearmAttributeIndex::Firerate] = firerateUpgrade;

	// Damage
	FirearmUpgrade* damageUpgrade = new FirearmUpgrade(
		FirearmAttributeIndex::Damage
	);
	damageUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	damageUpgrade->AddUpgrade(new UpgradeNode(25, 1.5f));
	damageUpgrade->AddUpgrade(new UpgradeNode(64, 1.9f));
	damageUpgrade->AddUpgrade(new UpgradeNode(189, 2.3f));
	firearmUpgradeMap[FirearmAttributeIndex::Damage] = damageUpgrade;

	// Max ammo
	FirearmUpgrade* magazineCapacityUpgrade = new FirearmUpgrade(
		FirearmAttributeIndex::MagazineCapacity
	);
	magazineCapacityUpgrade->AddUpgrade(new UpgradeNode(10, 1.2f));
	magazineCapacityUpgrade->AddUpgrade(new UpgradeNode(54, 1.3f));
	magazineCapacityUpgrade->AddUpgrade(new UpgradeNode(123, 1.5f));
	magazineCapacityUpgrade->AddUpgrade(new UpgradeNode(256, 2.0f));
	firearmUpgradeMap[FirearmAttributeIndex::MagazineCapacity] = magazineCapacityUpgrade;

	// Critical chance
	FirearmUpgrade* criticalDamageUpgrade = new FirearmUpgrade(
		FirearmAttributeIndex::CriticalDamage
	);
	criticalDamageUpgrade->AddUpgrade(new UpgradeNode(24, 0.3f));
	criticalDamageUpgrade->AddUpgrade(new UpgradeNode(74, 0.4f));
	criticalDamageUpgrade->AddUpgrade(new UpgradeNode(125, 0.55f));
	criticalDamageUpgrade->AddUpgrade(new UpgradeNode(299, 0.6f));
	criticalDamageUpgrade->AddUpgrade(new UpgradeNode(372, 0.7f));
	firearmUpgradeMap[FirearmAttributeIndex::CriticalDamage] = criticalDamageUpgrade;

}

Shop::UIElementIndex Shop::GetUIElementIndex(ShopMenuIndex shopMenuIndex) {

	switch (shopMenuIndex) {

	case ShopMenuIndex::Firearm_Main:
		return UIElementIndex::Shop_Navigation_Firearm;
		break;

	case ShopMenuIndex::Melee:
		return UIElementIndex::Shop_Navigation_Melee;
		break;

	case ShopMenuIndex::Utility:
		return UIElementIndex::Shop_Navigation_Utility;
		break;

	default:
		throw std::exception("Unknown menu index");

	}

}

void Shop::SwitchMenu(ShopMenuIndex targetMenuIndex) {

	if (targetMenuIndex == ShopMenuIndex::Firearm_Main && !currentFirearm)
		targetMenuIndex = ShopMenuIndex::Firearm_Selection;

	HideCurrentMenu();

	uiElementMap.at(NAVIGATION_INDEX_BY_SHOP_INDEX_MAP.at(currentMenuIndex))->GetComponent<Image>()->GetComponent<Image>()
		->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	uiElementMap.at(NAVIGATION_INDEX_BY_SHOP_INDEX_MAP.at(targetMenuIndex))->GetComponent<Image>()->GetComponent<Image>()
		->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonSelected), true);

	currentMenuIndex = targetMenuIndex;

	ShowCurrentMenu();

}

void Shop::UpdateAttributeList() {

	if (!currentFirearm)
		return;

	uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Content)->As<FirearmAttributeUIGroup>()->SetAttribute(currentFirearm, FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);

}

Shop::Shop() {

	if (instance)
		throw std::exception("Shop can only have one instance");

	instance = this;

	currentMenuIndex = ShopMenuIndex::Firearm_Main;

	firearmUpgradeMap = {};

	showShop = false;

	currentFirearm = nullptr;

	InitializeUpgrades();
	InitializeUI();

	SwitchMenu(currentMenuIndex);

	Hide();

}

void Shop::Update() {

	if (GameCore::GetKeyState(SDLK_TAB).started) {

		showShop = !showShop;

		if (showShop) {

			Player::Instance()->DisableInteraction();

			Show();

		} else {

			Player::Instance()->EnableInteraction();

			Hide();

		}

	}

}

void Shop::BuyUpgrade(FirearmAttributeIndex attribute) {

	if (!currentFirearm)
		return;

	auto it = firearmUpgradeMap.find(attribute);

	if (it == firearmUpgradeMap.end())
		throw std::exception("Shop: Trying to buy an invalid upgrade");

	if (PlayerStatistic::Instance()->TrySpendMoney((it->second)->NextUpgradeCost())) {

		(it->second)->UpgradeNext(currentFirearm);

		FirearmUpgradeUIGroup* upgradeUI = uiElementMap.at(UPGRADE_INDEX_BY_ATTRIBUTE_MAP.at(attribute))->As<FirearmUpgradeUIGroup>();
		upgradeUI->SetCost((it->second)->NextUpgradeCost());
		upgradeUI->SetAmount((it->second)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);

	}

	UpdateAttributeList();

}

void Shop::SelectFirearm(Firearm* firearm) {

	currentFirearm = firearm;

	uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->GetComponent<Image>()->LinkSprite(firearm->GetIconSprite(), true);

	uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->GetComponent<Text>()->LoadText(
		currentFirearm->GetName(), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Firearm_Main_GunLabel)
	);

	SwitchMenu(ShopMenuIndex::Firearm_Main);
	UpdateAttributeList();

}

Shop* Shop::Instance() { return instance; }