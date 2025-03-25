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
#include <ItemManager.h>
#include <ItemSelectionUI.h>
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

		uiElementMap.at(UIElementIndex::Firearm_SelectionGrid)->Enable();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:

		uiElementMap.at(UIElementIndex::Utility_ItemSelectionGrid)->Enable();
		uiElementMap.at(UIElementIndex::Utility_InfoBoard)->Enable();
		uiElementMap.at(UIElementIndex::Utility_BuyButton)->Enable();
		uiElementMap.at(UIElementIndex::Utility_ItemViewport)->Enable();
		uiElementMap.at(UIElementIndex::Utility_MoneyIcon)->Enable();
		uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->Enable();
		uiElementMap.at(UIElementIndex::Utility_ItemVisual)->Enable();
		uiElementMap.at(UIElementIndex::Utility_ItemLabel)->Enable();

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

		uiElementMap.at(UIElementIndex::Firearm_SelectionGrid)->Disable();

		break;

	case ShopMenuIndex::Melee:
		break;

	case ShopMenuIndex::Utility:

		uiElementMap.at(UIElementIndex::Utility_ItemSelectionGrid)->Disable();
		uiElementMap.at(UIElementIndex::Utility_InfoBoard)->Disable();
		uiElementMap.at(UIElementIndex::Utility_BuyButton)->Disable();
		uiElementMap.at(UIElementIndex::Utility_ItemViewport)->Disable();
		uiElementMap.at(UIElementIndex::Utility_MoneyIcon)->Disable();
		uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->Disable();
		uiElementMap.at(UIElementIndex::Utility_ItemVisual)->Disable();
		uiElementMap.at(UIElementIndex::Utility_ItemLabel)->Disable();

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
		return true;
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
		return true;
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
		return true;
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
	firearmViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmViewport), true);
	firearmViewport_image->showOnScreen = true;
	firearmViewport_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_GunViewport),
		firearmViewport_image->transform->scale
	);
	Button* firearmViewport_button = uiElementMap.at(UIElementIndex::Firearm_Main_GunViewport)->AddComponent<Button>();
	firearmViewport_button->backgroundColor = Color::TRANSPARENT;
	firearmViewport_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Firearm_Selection);
		return true;
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
	firearmSelectionUI->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_SelectionGrid));
	std::vector<Firearm*> firearmList = Player::Instance()->GetFirearmList();
	for (Firearm* firearm : firearmList)
		firearmSelectionUI->AddFirearm(firearm);
	uiElementMap[UIElementIndex::Firearm_SelectionGrid] = firearmSelectionUI;

	/// >>>
	/// --- ATTRIBUTE FRAME ---
	/// >>>
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Frame] = new GameObject("Attribute frame", Layer::Menu);
	Image* firearmAttributeFrame_image = uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->AddComponent<Image>();
	firearmAttributeFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmAttributeFrame), true);
	firearmAttributeFrame_image->showOnScreen = true;
	firearmAttributeFrame_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Frame),
		firearmAttributeFrame_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Firearm_Main_Attribute_Frame)->Render = [firearmAttributeFrame_image]() {
		firearmAttributeFrame_image->Render();
		};

	/// >>>
	/// --- ATTRIBUTE CONTENT --- 
	/// >>>
	FirearmAttributeUIGroup* attributeUIGroup = new FirearmAttributeUIGroup;
	attributeUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Content));
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Content] = attributeUIGroup;

	/// >>>
	/// --- UTILITY INFO BOARD ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_InfoBoard] = new GameObject("Utility game object", Layer::Menu);
	Image* utilityInfoBoard_image = uiElementMap.at(UIElementIndex::Utility_InfoBoard)->AddComponent<Image>();
	utilityInfoBoard_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityInfoBoard), true);
	utilityInfoBoard_image->showOnScreen = true;
	utilityInfoBoard_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_InfoBoard),
		utilityInfoBoard_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Utility_InfoBoard)->Render = [utilityInfoBoard_image]() {
		utilityInfoBoard_image->Render();
		};

	/// >>>
	/// --- UTILITY ITEM VIEWPORT ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_ItemViewport] = new GameObject("Utility viewport", Layer::Menu);
	Image* utilityItemViewport_image = uiElementMap.at(UIElementIndex::Utility_ItemViewport)->AddComponent<Image>();
	utilityItemViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemViewport), true);
	utilityItemViewport_image->showOnScreen = true;
	utilityItemViewport_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_ItemViewport),
		utilityItemViewport_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Utility_ItemViewport)->Render = [utilityItemViewport_image]() {
		utilityItemViewport_image->Render();
		};

	/// >>>
	/// --- UTILITY BUY BUTTON ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_BuyButton] = new GameObject("Utility buy button", Layer::Menu);
	Image* utilityBuyButton_image = uiElementMap.at(UIElementIndex::Utility_BuyButton)->AddComponent<Image>();
	utilityBuyButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityBuyButton), true);
	utilityBuyButton_image->showOnScreen = true;
	utilityBuyButton_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_BuyButton),
		utilityBuyButton_image->transform->scale
	);
	Button* utilityInfoBoard_button = uiElementMap.at(UIElementIndex::Utility_BuyButton)->AddComponent<Button>();
	utilityInfoBoard_button->backgroundColor = Color::TRANSPARENT;
	utilityInfoBoard_button->OnClick = [utilityInfoBoard_button]() {
		Shop::Instance()->BuyItem();
		return true;
		};
	uiElementMap.at(UIElementIndex::Utility_BuyButton)->Render = [utilityBuyButton_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityBuyButton_image->Render();
		};

	/// >>>
	/// --- ITEM SELECTION GRID ---
	/// >>>
	ItemSelectionUI* itemSelectionUI = new ItemSelectionUI;
	itemSelectionUI->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_ItemSelectionGrid));
	itemSelectionUI->AddItem(ItemIndex::MedKit);
	itemSelectionUI->AddItem(ItemIndex::Shotgun_Beretta1301);
	uiElementMap[UIElementIndex::Utility_ItemSelectionGrid] = itemSelectionUI;

	/// >>>
	/// --- MONEY ICON ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_MoneyIcon] = new GameObject("Utility money icon", Layer::Menu);
	Image* utilityMoneyIcon_image = uiElementMap.at(UIElementIndex::Utility_MoneyIcon)->AddComponent<Image>();
	utilityMoneyIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	utilityMoneyIcon_image->showOnScreen = true;
	utilityMoneyIcon_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_MoneyIcon),
		utilityMoneyIcon_image->transform->scale
	);
	uiElementMap.at(UIElementIndex::Utility_MoneyIcon)->Render = [utilityMoneyIcon_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityMoneyIcon_image->Render();
		};

	/// >>>
	/// --- MONEY LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_MoneyLabel] = new GameObject("Utility money label", Layer::Menu);
	Text* utilityMoneyLabel_text = uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->AddComponent<Text>();
	utilityMoneyLabel_text->LoadText("12,000", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_MoneyLabel));
	utilityMoneyLabel_text->showOnScreen = true;
	Align::Left(utilityMoneyLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	Align::MiddleVertically(utilityMoneyLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	utilityMoneyLabel_text->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_MoneyLabel);
	uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->Render = [utilityMoneyLabel_text]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityMoneyLabel_text->Render();
		};

	/// >>>
	/// --- ITEM VISUAL ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_ItemVisual] = new GameObject("Utility money icon", Layer::Menu);
	Image* utilityItemVisual_image = uiElementMap.at(UIElementIndex::Utility_ItemVisual)->AddComponent<Image>();
	utilityItemVisual_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	utilityItemVisual_image->showOnScreen = true;
	utilityItemVisual_image->transform->position = uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform->position;
	uiElementMap.at(UIElementIndex::Utility_ItemVisual)->Render = [utilityItemVisual_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityItemVisual_image->Render();
		};

	/// >>>
	/// --- ITEM LABEL ---
	/// >>>
	uiElementMap[UIElementIndex::Utility_ItemLabel] = new GameObject("Utility item label", Layer::Menu);
	Text* utilityItemLabel_text = uiElementMap.at(UIElementIndex::Utility_ItemLabel)->AddComponent<Text>();
	utilityItemLabel_text->LoadText("<Item Name>", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemLabel));
	utilityItemLabel_text->showOnScreen = true;
	Align::Bottom(utilityItemLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform);
	Align::MiddleHorizontally(utilityItemLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform);
	utilityItemLabel_text->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_ItemLabel);
	uiElementMap.at(UIElementIndex::Utility_ItemLabel)->Render = [utilityItemLabel_text]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityItemLabel_text->Render();
		};

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
	currentItemIndex = ItemIndex::None;

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

	ItemManager::Instance()->LinkItemIcon(firearm->GetIndex(), uiElementMap.at(UIElementIndex::Firearm_Main_GunViewportVisual)->GetComponent<Image>());

	uiElementMap.at(UIElementIndex::Firearm_Main_GunLabel)->GetComponent<Text>()->LoadText(
		currentFirearm->GetName(), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Firearm_Main_GunLabel)
	);

	SwitchMenu(ShopMenuIndex::Firearm_Main);
	UpdateAttributeList();

}

void Shop::SelectItem(ItemIndex itemIndex) {

	currentItemIndex = itemIndex;

	ItemManager::Instance()->LinkItemIcon(itemIndex, uiElementMap.at(UIElementIndex::Utility_ItemVisual)->GetComponent<Image>());
	uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->GetComponent<Text>()->LoadText(
		std::to_string(ItemManager::Instance()->GetItemPrice(itemIndex)), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_MoneyLabel)
	);
	Align::Left(uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_MoneyLabel);

	uiElementMap.at(UIElementIndex::Utility_ItemLabel)->GetComponent<Text>()->LoadText(
		ItemManager::Instance()->GetItemName(itemIndex), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemLabel)
	);

}

void Shop::BuyItem() {

	if (currentItemIndex == ItemIndex::None)
		return;

	if (!PlayerStatistic::Instance()->TrySpendMoney(ItemManager::Instance()->GetItemPrice(currentItemIndex)))
		return;

	Player::Instance()->GiveItem(currentItemIndex);

}

ItemIndex Shop::GetSelectedItem() const { return currentItemIndex; }

Shop* Shop::Instance() { return instance; }