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
#include <SkillInfoUI.h>
#include <SkillList.h>
#include <Texture.h>
#include <Utils.h>

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
	uiElementMap.at(UIElementIndex::Shop_Navigation_Skill)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Utility)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Firearm_Label)->Enable();
	uiElementMap.at(UIElementIndex::Shop_Navigation_Skill_Label)->Enable();
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

	case ShopMenuIndex::Skill:

		uiElementMap.at(UIElementIndex::Skill_List)->Enable();
		uiElementMap.at(UIElementIndex::Skill_InfoBoard)->Enable();
		uiElementMap.at(UIElementIndex::Skill_PointIcon)->Enable();
		uiElementMap.at(UIElementIndex::Skill_PointLabel)->Enable();

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
		uiElementMap.at(UIElementIndex::Utility_ItemStackLabel)->Enable();

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

	case ShopMenuIndex::Skill:

		uiElementMap.at(UIElementIndex::Skill_List)->Disable();
		uiElementMap.at(UIElementIndex::Skill_InfoBoard)->Disable();
		uiElementMap.at(UIElementIndex::Skill_PointIcon)->Disable();
		uiElementMap.at(UIElementIndex::Skill_PointLabel)->Disable();

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
		uiElementMap.at(UIElementIndex::Utility_ItemStackLabel)->Disable();

		break;

	}

}

void Shop::InitializeUI() {
	/// >>>
	/// --- BACKGROUND ---
	/// >>>
	GameObject* shopBackground = GameObject::Instantiate("Shop Background", Layer::Menu);
	Image* shopBackground_image = shopBackground->AddComponent<Image>();
	shopBackground_image->showOnScreen = true;
	shopBackground_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_Background), true);
	shopBackground_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Background),
		shopBackground_image->transform->scale
	);
	shopBackground->Render = [shopBackground_image]() {
		shopBackground_image->Render();
		};
	uiElementMap[UIElementIndex::Shop_Background] = shopBackground;

	/// >>>
	/// --- FIREARM NAVIGATION ---
	/// >>>
	GameObject* navigationFirearm = GameObject::Instantiate("Navigation Firearm", Layer::Menu);
	Image* navigationFirearm_image = navigationFirearm->AddComponent<Image>();
	navigationFirearm_image->showOnScreen = true;
	navigationFirearm_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationFirearm_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Firearm),
		navigationFirearm_image->transform->scale
	);
	Button* navigationFirearm_button = navigationFirearm->AddComponent<Button>();
	navigationFirearm_button->backgroundColor = Color::WHITE;
	navigationFirearm_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Firearm_Main);
		return true;
		};
	navigationFirearm->Render = [navigationFirearm_image]() {
		navigationFirearm_image->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Firearm] = navigationFirearm;

	/// >>>
	/// --- FIREARM NAVIGATION LABEL ---
	/// >>>
	GameObject* navigationFirearmLabel = GameObject::Instantiate("Navigation Firearm Label", Layer::Menu);
	Text* navigationFirearmLabel_text = navigationFirearmLabel->AddComponent<Text>();
	navigationFirearmLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Firearm_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Firearm_Label)
	);
	navigationFirearmLabel_text->showOnScreen = true;
	navigationFirearmLabel_text->transform->position = navigationFirearm_image->transform->position;
	navigationFirearmLabel->Render = [navigationFirearmLabel_text]() {
		navigationFirearmLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Firearm_Label] = navigationFirearmLabel;

	/// >>>
	/// --- SKILL NAVIGATION ---
	/// >>>
	GameObject* navigationSkill = GameObject::Instantiate("Navigation Melee", Layer::Menu);
	Image* navigationSkill_image = navigationSkill->AddComponent<Image>();
	navigationSkill_image->showOnScreen = true;
	navigationSkill_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationSkill_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Skill),
		navigationSkill_image->transform->scale
	);
	Button* navigationMelee_button = navigationSkill->AddComponent<Button>();
	navigationMelee_button->backgroundColor = Color::WHITE;
	navigationMelee_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Skill);
		return true;
		};
	navigationSkill->Render = [navigationSkill_image]() {
		navigationSkill_image->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Skill] = navigationSkill;

	/// >>>
	/// --- SKILL NAVIGATION LABEL ---
	/// >>>
	GameObject* navigationSkillLabel = GameObject::Instantiate("Navigation Melee Label", Layer::Menu);
	Text* navigationSkillLabel_text = navigationSkillLabel->AddComponent<Text>();
	navigationSkillLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Skill_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Skill_Label)
	);
	navigationSkillLabel_text->showOnScreen = true;
	navigationSkillLabel_text->transform->position = navigationSkill_image->transform->position;
	navigationSkillLabel->Render = [navigationSkillLabel_text]() {
		navigationSkillLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Skill_Label] = navigationSkillLabel;

	/// >>>
	/// --- UTILITY NAVIGATION ---
	/// >>>
	GameObject* navigationUtility = GameObject::Instantiate("Navigation Utility", Layer::Menu);
	Image* navigationUtility_image = navigationUtility->AddComponent<Image>();
	navigationUtility_image->showOnScreen = true;
	navigationUtility_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_NavigationButtonUnselected), true);
	navigationUtility_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Shop_Navigation_Utility),
		navigationUtility_image->transform->scale
	);
	Button* navigationUtility_button = navigationUtility->AddComponent<Button>();
	navigationUtility_button->backgroundColor = Color::WHITE;
	navigationUtility_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Utility);
		return true;
		};
	navigationUtility->Render = [navigationUtility_image]() {
		navigationUtility_image->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Utility] = navigationUtility;

	/// >>>
	/// --- UTILITY NAVIGATION LABEL ---
	/// >>>
	GameObject* navigationUtilityLabel = GameObject::Instantiate("Navigation Utility Label", Layer::Menu);
	Text* navigationUtilityLabel_text = navigationUtilityLabel->AddComponent<Text>();
	navigationUtilityLabel_text->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Shop_Navigation_Utility_Label),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Shop_Navigation_Utility_Label)
	);
	navigationUtilityLabel_text->showOnScreen = true;
	navigationUtilityLabel_text->transform->position = navigationUtility_image->transform->position;
	navigationUtilityLabel->Render = [navigationUtilityLabel_text]() {
		navigationUtilityLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Shop_Navigation_Utility_Label] = navigationUtilityLabel;

	/// >>>
	/// --- DAMAGE UPGRADE ---
	/// >>>
	FirearmUpgradeUIGroup* upgradeDamageUIGroup = GameObject::Instantiate<FirearmUpgradeUIGroup>("Damage Upgrade UI Group", Layer::Menu);
	upgradeDamageUIGroup->SetAttribute(FirearmAttributeIndex::Damage);
	upgradeDamageUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	upgradeDamageUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::Damage)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeDamageUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::Damage)->NextUpgradeCost());
	upgradeDamageUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Damage));
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_Damage] = upgradeDamageUIGroup;

	/// >>>
	/// --- CRITICAL DAMAGE UPGRADE ---
	/// >>>
	FirearmUpgradeUIGroup* upgradeCriticalDamageUIGroup = GameObject::Instantiate<FirearmUpgradeUIGroup>("Critical Damage Upgrade UI Group", Layer::Menu);
	upgradeCriticalDamageUIGroup->SetAttribute(FirearmAttributeIndex::CriticalDamage);
	upgradeCriticalDamageUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	upgradeCriticalDamageUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::CriticalDamage)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeCriticalDamageUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::CriticalDamage)->NextUpgradeCost());
	upgradeCriticalDamageUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_CriticalDamage));
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_CriticalDamage] = upgradeCriticalDamageUIGroup;

	/// >>>
	/// --- FIRERATE UPGRADE ---
	/// >>>
	FirearmUpgradeUIGroup* upgradeFirerateUIGroup = GameObject::Instantiate<FirearmUpgradeUIGroup>("Firerate Upgrade UI Group", Layer::Menu);
	upgradeFirerateUIGroup->SetAttribute(FirearmAttributeIndex::Firerate);
	upgradeFirerateUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	upgradeFirerateUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::Firerate)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeFirerateUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::Firerate)->NextUpgradeCost());
	upgradeFirerateUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_Firerate));
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_Firerate] = upgradeFirerateUIGroup;

	/// >>>
	/// --- MAGAZINE CAPACITY UPGRADE ---
	/// >>>
	FirearmUpgradeUIGroup* upgradeMagazineCapacityUIGroup = GameObject::Instantiate<FirearmUpgradeUIGroup>("Magazine capacity Upgrade UI Group", Layer::Menu);
	upgradeMagazineCapacityUIGroup->SetAttribute(FirearmAttributeIndex::MagazineCapacity);
	upgradeMagazineCapacityUIGroup->SetLabel(UI_LABEL_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetDescriptionPrefix(UPGRADE_DESCRIPTION_PREFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetDescriptionSuffix(UPGRADE_DESCRIPTION_SUFFIX_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	upgradeMagazineCapacityUIGroup->SetAmount(firearmUpgradeMap.at(FirearmAttributeIndex::MagazineCapacity)->NextUpgradeAmount(), FIREARM_ATTRIBUTE_AMOUNT_DECIMAL);
	upgradeMagazineCapacityUIGroup->SetCost(firearmUpgradeMap.at(FirearmAttributeIndex::MagazineCapacity)->NextUpgradeCost());
	upgradeMagazineCapacityUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity));
	uiElementMap[UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity] = upgradeMagazineCapacityUIGroup;

	/// >>>
	/// --- FIREARM VIEWPORT ---
	/// >>>
	GameObject* firearmViewport = GameObject::Instantiate("Firearm Viewport", Layer::Menu);
	Image* firearmViewport_image = firearmViewport->AddComponent<Image>();
	firearmViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmViewport), true);
	firearmViewport_image->showOnScreen = true;
	firearmViewport_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_GunViewport),
		firearmViewport_image->transform->scale
	);
	Button* firearmViewport_button = firearmViewport->AddComponent<Button>();
	firearmViewport_button->backgroundColor = Color::TRANSPARENT;
	firearmViewport_button->OnClick = [this]() {
		SwitchMenu(ShopMenuIndex::Firearm_Selection);
		return true;
		};
	firearmViewport->Render = [firearmViewport_image]() {
		firearmViewport_image->Render();
		};
	uiElementMap[UIElementIndex::Firearm_Main_GunViewport] = firearmViewport;

	/// >>>
	/// --- FIREARM VIEWPORT VISUAL ---
	/// >>>
	GameObject* firearmViewportVisual = GameObject::Instantiate("Firearm Viewport Visual", Layer::Menu);
	Image* firearmViewportVisual_image = firearmViewportVisual->AddComponent<Image>();
	firearmViewportVisual_image->showOnScreen = true;
	firearmViewportVisual_image->transform->position = firearmViewport_image->transform->position;
	firearmViewportVisual->Render = [firearmViewportVisual_image]() {
		firearmViewportVisual_image->Render();
		};
	uiElementMap[UIElementIndex::Firearm_Main_GunViewportVisual] = firearmViewportVisual;

	/// >>>
	/// --- FIREARM LABEL ---
	/// >>>
	GameObject* firearmLabel = GameObject::Instantiate("Firearm Label", Layer::Menu);
	Text* firearmLabel_text = firearmLabel->AddComponent<Text>();
	firearmLabel_text->LoadText("<Gun Label>", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Firearm_Main_GunLabel));
	firearmLabel_text->showOnScreen = true;
	firearmLabel_text->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_GunLabel),
		UI_ELEMENT_SCALE_MAP.at(UIElementIndex::Firearm_Main_GunLabel)
	);
	firearmLabel->Render = [firearmLabel_text]() {
		firearmLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Firearm_Main_GunLabel] = firearmLabel;

	/// >>>
	/// --- FIREARM SELECTION GRID ---
	/// >>>
	FirearmSelectionUI* firearmSelectionUI = GameObject::Instantiate<FirearmSelectionUI>();
	firearmSelectionUI->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_SelectionGrid));
	std::vector<Firearm*> firearmList = Player::Instance()->GetFirearmList();
	for (Firearm* firearm : firearmList)
		firearmSelectionUI->AddFirearm(firearm);
	uiElementMap[UIElementIndex::Firearm_SelectionGrid] = firearmSelectionUI;

	/// >>>
	/// --- ATTRIBUTE FRAME ---
	/// >>>
	GameObject* firearmAttributeFrame = GameObject::Instantiate("Attribute frame", Layer::Menu);
	Image* firearmAttributeFrame_image = firearmAttributeFrame->AddComponent<Image>();
	firearmAttributeFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_FirearmAttributeFrame), true);
	firearmAttributeFrame_image->showOnScreen = true;
	firearmAttributeFrame_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Frame),
		firearmAttributeFrame_image->transform->scale
	);
	firearmAttributeFrame->Render = [firearmAttributeFrame_image]() {
		firearmAttributeFrame_image->Render();
		};
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Frame] = firearmAttributeFrame;

	/// >>>
	/// --- ATTRIBUTE CONTENT --- 
	/// >>>
	FirearmAttributeUIGroup* attributeUIGroup = GameObject::Instantiate<FirearmAttributeUIGroup>();
	attributeUIGroup->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Firearm_Main_Attribute_Content));
	uiElementMap[UIElementIndex::Firearm_Main_Attribute_Content] = attributeUIGroup;

	/// >>>
	/// --- UTILITY INFO BOARD ---
	/// >>>
	GameObject* utilityInfoBoard = GameObject::Instantiate("Utility game object", Layer::Menu);
	Image* utilityInfoBoard_image = utilityInfoBoard->AddComponent<Image>();
	utilityInfoBoard_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityInfoBoard), true);
	utilityInfoBoard_image->showOnScreen = true;
	utilityInfoBoard_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_InfoBoard),
		utilityInfoBoard_image->transform->scale
	);
	utilityInfoBoard->Render = [utilityInfoBoard_image]() {
		utilityInfoBoard_image->Render();
		};
	uiElementMap[UIElementIndex::Utility_InfoBoard] = utilityInfoBoard;

	/// >>>
	/// --- UTILITY ITEM VIEWPORT ---
	/// >>>
	GameObject* utilityItemViewport = GameObject::Instantiate("Utility viewport", Layer::Menu);
	Image* utilityItemViewport_image = utilityItemViewport->AddComponent<Image>();
	utilityItemViewport_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityItemViewport), true);
	utilityItemViewport_image->showOnScreen = true;
	utilityItemViewport_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_ItemViewport),
		utilityItemViewport_image->transform->scale
	);
	utilityItemViewport->Render = [utilityItemViewport_image]() {
		utilityItemViewport_image->Render();
		};
	uiElementMap[UIElementIndex::Utility_ItemViewport] = utilityItemViewport;

	/// >>>
	/// --- UTILITY ITEM STACK LABEL ---
	/// >>>
	GameObject* utilityItemStackLabel = GameObject::Instantiate("Utility Item Stack Label", Layer::Menu);
	Text* utilityItemStackLabel_text = utilityItemStackLabel->AddComponent<Text>();
	utilityItemStackLabel_text->LoadText("", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemStackLabel));
	utilityItemStackLabel_text->showOnScreen = true;
	Align::Right(utilityItemStackLabel->transform, utilityItemViewport->transform);
	Align::Bottom(utilityItemStackLabel->transform, utilityItemViewport->transform);
	utilityItemStackLabel->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_ItemStackLabel);
	utilityItemStackLabel->Render = [utilityItemStackLabel_text]() {
		utilityItemStackLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Utility_ItemStackLabel] = utilityItemStackLabel;

	/// >>>
	/// --- UTILITY BUY BUTTON ---
	/// >>>
	GameObject* utilityBuyButton = GameObject::Instantiate("Utility buy button", Layer::Menu);
	Image* utilityBuyButton_image = utilityBuyButton->AddComponent<Image>();
	utilityBuyButton_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Shop_UtilityBuyButton), true);
	utilityBuyButton_image->showOnScreen = true;
	utilityBuyButton_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_BuyButton),
		utilityBuyButton_image->transform->scale
	);
	Button* utilityInfoBoard_button = utilityBuyButton->AddComponent<Button>();
	utilityInfoBoard_button->backgroundColor = Color::TRANSPARENT;
	utilityInfoBoard_button->OnClick = [utilityInfoBoard_button]() {
		Shop::Instance()->BuyItem();
		return true;
		};
	utilityBuyButton->Render = [utilityBuyButton_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityBuyButton_image->Render();
		};
	uiElementMap[UIElementIndex::Utility_BuyButton] = utilityBuyButton;

	/// >>>
	/// --- ITEM SELECTION GRID ---
	/// >>>
	ItemSelectionUI* itemSelectionUI = GameObject::Instantiate<ItemSelectionUI>();
	itemSelectionUI->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_ItemSelectionGrid));
	itemSelectionUI->AddItem(ItemIndex::MedKit);
	itemSelectionUI->AddItem(ItemIndex::Ammo_Slug);
	itemSelectionUI->AddItem(ItemIndex::Ammo_9mm);
	itemSelectionUI->AddItem(ItemIndex::Ammo_556);
	uiElementMap[UIElementIndex::Utility_ItemSelectionGrid] = itemSelectionUI;

	/// >>>
	/// --- MONEY ICON ---
	/// >>>
	GameObject* utilityMoneyIcon = GameObject::Instantiate("Utility money icon", Layer::Menu);
	Image* utilityMoneyIcon_image = utilityMoneyIcon->AddComponent<Image>();
	utilityMoneyIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	utilityMoneyIcon_image->showOnScreen = true;
	utilityMoneyIcon_image->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Utility_MoneyIcon),
		utilityMoneyIcon_image->transform->scale
	);
	utilityMoneyIcon->Render = [utilityMoneyIcon_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityMoneyIcon_image->Render();
		};
	uiElementMap[UIElementIndex::Utility_MoneyIcon] = utilityMoneyIcon;

	/// >>>
	/// --- MONEY LABEL ---
	/// >>>
	GameObject* utilityMoneyLabel = GameObject::Instantiate("Utility money label", Layer::Menu);
	Text* utilityMoneyLabel_text = utilityMoneyLabel->AddComponent<Text>();
	utilityMoneyLabel_text->LoadText("12,000", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_MoneyLabel));
	utilityMoneyLabel_text->showOnScreen = true;
	Align::Left(utilityMoneyLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	Align::MiddleVertically(utilityMoneyLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	utilityMoneyLabel_text->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_MoneyLabel);
	utilityMoneyLabel->Render = [utilityMoneyLabel_text]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityMoneyLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Utility_MoneyLabel] = utilityMoneyLabel;

	/// >>>
	/// --- ITEM VISUAL ---
	/// >>>
	GameObject* utilityItemVisual = GameObject::Instantiate("Utility money icon", Layer::Menu);
	Image* utilityItemVisual_image = utilityItemVisual->AddComponent<Image>();
	utilityItemVisual_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_MoneyIcon), true);
	utilityItemVisual_image->showOnScreen = true;
	utilityItemVisual_image->transform->position = uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform->position;
	utilityItemVisual->Render = [utilityItemVisual_image]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityItemVisual_image->Render();
		};
	uiElementMap[UIElementIndex::Utility_ItemVisual] = utilityItemVisual;

	/// >>>
	/// --- ITEM LABEL ---
	/// >>>
	GameObject* utilityItemLabel = GameObject::Instantiate("Utility item label", Layer::Menu);
	Text* utilityItemLabel_text = utilityItemLabel->AddComponent<Text>();
	utilityItemLabel_text->LoadText("<Item Name>", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemLabel));
	utilityItemLabel_text->showOnScreen = true;
	Align::Bottom(utilityItemLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform);
	Align::MiddleHorizontally(utilityItemLabel_text->transform, uiElementMap.at(UIElementIndex::Utility_ItemViewport)->transform);
	utilityItemLabel_text->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_ItemLabel);
	utilityItemLabel->Render = [utilityItemLabel_text]() {
		if (Shop::Instance()->GetSelectedItem() != ItemIndex::None)
			utilityItemLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Utility_ItemLabel] = utilityItemLabel;

	/// >>>
	/// --- SKILL INFO BOARD ---
	/// >>>
	uiElementMap[UIElementIndex::Skill_InfoBoard] = GameObject::Instantiate<SkillInfoUI>();

	/// >>>
	/// --- SKILL LIST ---
	/// >>>
	SkillList* skillList = GameObject::Instantiate<SkillList>();
	skillList->AddSkill(SkillListIndex::First, new SkillNode{
		.skillPoint = 1,
		.value = 120.0f,
		.name = "Health I",
		.description = "Increase Player Max HP to 120",
		.playerAttribute = PlayerAttribute::MaxHealth,
		});
	skillList->AddSkill(SkillListIndex::First, new SkillNode{
		.skillPoint = 2,
		.value = 130.0f,
		.name = "Health II",
		.description = "Increase Player Max HP to 130",
		.playerAttribute = PlayerAttribute::MaxHealth,
		});
	skillList->AddSkill(SkillListIndex::First, new SkillNode{
		.skillPoint = 5,
		.value = 150.0f,
		.name = "Health III",
		.description = "Increase Player Max HP to 150",
		.playerAttribute = PlayerAttribute::MaxHealth,
		});
	skillList->AddSkill(SkillListIndex::Second, new SkillNode{
		.skillPoint = 1,
		.value = 2.9f,
		.name = "Quick Hand",
		.description = "Increase reload speed by 20%",
		.playerAttribute = PlayerAttribute::ReloadSpeed,
		});
	skillList->AddSkill(SkillListIndex::Third, new SkillNode{
		.skillPoint = 1,
		.value = 0.35f,
		.name = "Accuracy I",
		.description = "Increase accuracy to 35%",
		.playerAttribute = PlayerAttribute::Accuracy,
		});
	skillList->AddSkill(SkillListIndex::Third, new SkillNode{
		.skillPoint = 2,
		.value = 0.4f,
		.name = "Accuracy II",
		.description = "Increase accuracy to 40%",
		.playerAttribute = PlayerAttribute::Accuracy,
		});
	skillList->AddSkill(SkillListIndex::Third, new SkillNode{
		.skillPoint = 3,
		.value = 0.45f,
		.name = "Accuracy III",
		.description = "Increase accuracy to 45%",
		.playerAttribute = PlayerAttribute::Accuracy,
		});
	skillList->AddSkill(SkillListIndex::Third, new SkillNode{
		.skillPoint = 4,
		.value = 0.5f,
		.name = "Accuracy IV",
		.description = "Increase accuracy to 50%",
		.playerAttribute = PlayerAttribute::Accuracy,
		});
	skillList->SetPosition(UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Skill_List));
	uiElementMap[UIElementIndex::Skill_List] = skillList;

	/// >>>
	/// --- SKILL POINT ICON ---
	/// >>>

	GameObject* skillPointIcon = GameObject::Instantiate("Skill Point Icon", Layer::Menu);
	Image* skillPointIcon_image = skillPointIcon->AddComponent<Image>();
	skillPointIcon_image->showOnScreen = true;
	skillPointIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Icon_SkillPointIcon), true);
	skillPointIcon->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Skill_PointIcon), skillPointIcon->transform->scale
	);
	skillPointIcon->Render = [skillPointIcon_image]() {
		skillPointIcon_image->Render();
		};
	uiElementMap[UIElementIndex::Skill_PointIcon] = skillPointIcon;

	/// >>>
	/// --- SKILL POINT LABEL ---
	/// >>>

	GameObject* skillPointLabel = GameObject::Instantiate("Skill Point Label", Layer::Menu);
	Text* skillPointLabel_text = skillPointLabel->AddComponent<Text>();
	skillPointLabel_text->showOnScreen = true;
	skillPointLabel_text->LoadText("0", Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Skill_PointLabel));
	skillPointLabel->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Skill_PointLabel), skillPointLabel->transform->scale
	);
	skillPointLabel->Render = [skillPointLabel_text]() {
		skillPointLabel_text->Render();
		};
	uiElementMap[UIElementIndex::Skill_PointLabel] = skillPointLabel;

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

	case ShopMenuIndex::Skill:
		return UIElementIndex::Shop_Navigation_Skill;
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

		showShop ? Show() : Hide();

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

	// Update viewport
	ItemManager::Instance()->LinkItemIcon(itemIndex, uiElementMap.at(UIElementIndex::Utility_ItemVisual)->GetComponent<Image>());
	uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->GetComponent<Text>()->LoadText(
		std::to_string(ItemManager::Instance()->GetItemPrice(itemIndex)), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_MoneyLabel)
	);
	Align::Left(uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->transform, uiElementMap.at(UIElementIndex::Utility_BuyButton)->transform);
	uiElementMap.at(UIElementIndex::Utility_MoneyLabel)->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_MoneyLabel);

	// Update label
	uiElementMap.at(UIElementIndex::Utility_ItemLabel)->GetComponent<Text>()->LoadText(
		ItemManager::Instance()->GetItemName(itemIndex), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemLabel)
	);

	// Update stack label
	GameObject* itemStackLabel = uiElementMap.at(UIElementIndex::Utility_ItemStackLabel);
	GameObject* viewport = uiElementMap.at(UIElementIndex::Utility_ItemViewport);
	itemStackLabel->GetComponent<Text>()->LoadText(
		UI_LABEL_MAP.at(UIElementIndex::Utility_ItemStackLabel) + std::to_string(ItemManager::Instance()->GetItemShopStack(itemIndex)),
		Color::WHITE,
		UI_FONT_SIZE_MAP.at(UIElementIndex::Utility_ItemStackLabel)
	);
	Align::Right(itemStackLabel->transform, viewport->transform);
	Align::Bottom(itemStackLabel->transform, viewport->transform);
	itemStackLabel->transform->position += UI_ELEMENT_OFFSET_MAP.at(UIElementIndex::Utility_ItemStackLabel);

}

void Shop::BuyItem() {

	if (currentItemIndex == ItemIndex::None)
		return;

	if (!PlayerStatistic::Instance()->TrySpendMoney(ItemManager::Instance()->GetItemPrice(currentItemIndex)))
		return;

	Player::Instance()->GiveItem(currentItemIndex, ItemManager::Instance()->GetItemShopStack(currentItemIndex));

}

void Shop::SelectSkillNode(SkillNode* skillNode) {

	uiElementMap.at(UIElementIndex::Skill_InfoBoard)->As<SkillInfoUI>()->UpdateSkillInfo(skillNode);

}

void Shop::BuySkillNode() {

	SkillList* skillList = uiElementMap.at(UIElementIndex::Skill_List)->As<SkillList>();

	if (PlayerStatistic::Instance()->TryConsumeSkillPoint(skillList->GetCurrentSkillCost()))
		skillList->UpgradeSelected();

}

void Shop::UpdateSkillPoint(int amount) {

	GameObject* skillPointLabel = uiElementMap.at(UIElementIndex::Skill_PointLabel);
	skillPointLabel->GetComponent<Text>()->LoadText(
		std::to_string(amount), Color::WHITE, UI_FONT_SIZE_MAP.at(UIElementIndex::Skill_PointLabel)
	);
	skillPointLabel->transform->position = Math::SDLToC00(
		UI_ELEMENT_POSITION_MAP.at(UIElementIndex::Skill_PointLabel), skillPointLabel->transform->scale
	);

}

ItemIndex Shop::GetSelectedItem() const { return currentItemIndex; }

Shop* Shop::Instance() { return instance; }