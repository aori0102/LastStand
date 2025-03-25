﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <string>
#include <vector>

#include <Firearm.h>
#include <GameComponent.h>
#include <RenderManager.h>
#include <Type.h>

struct ButtonUIGroup;
class Player;
class Firearm;
class FirearmUpgrade;

// Upgrades
class UpgradeNode {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

	int cost;
	float amount;
	UpgradeNode* next;

	friend class Shop;
	friend class FirearmUpgrade;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

	UpgradeNode(int initCost, float initAmount)
		: cost(initCost), amount(initAmount), next(nullptr) {}

};

class Shop : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	// For menu navigation
	enum class ShopMenuIndex {

		Firearm_Main,
		Firearm_Selection,
		Melee,
		Utility,

	};

	enum class UIElementIndex {

		Shop_Background,
		Shop_Navigation_Firearm,
		Shop_Navigation_Firearm_Label,
		Shop_Navigation_Melee,
		Shop_Navigation_Melee_Label,
		Shop_Navigation_Utility,
		Shop_Navigation_Utility_Label,
		Firearm_Main_Attribute_Frame,
		Firearm_Main_Attribute_Content,
		Firearm_Main_GunViewport,
		Firearm_Main_GunViewportVisual,
		Firearm_Main_GunLabel,
		Firearm_Main_InfoBoard,
		Firearm_Main_Upgrade_Damage,
		Firearm_Main_Upgrade_CriticalDamage,
		Firearm_Main_Upgrade_Firerate,
		Firearm_Main_Upgrade_MagazineCapacity,
		Firearm_SelectionGrid,
		Melee,
		Utility_ItemSelectionGrid,
		Utility_InfoBoard,
		Utility_ItemViewport,
		Utility_BuyButton,
		Utility_ItemVisual,
		Utility_MoneyIcon,
		Utility_MoneyLabel,
		Utility_ItemLabel,
		Utility_ItemDescription,

	};

	const float UPGRADE_DESCRIPTION_MARGIN = 40.0f;
	const float FIREARM_ATTRIBUTE_VALUE_LEFT = 1075.0f;
	const float GUN_LABEL_OFFSET = 50.0f;
	const int GUN_LABEL_FONT_SIZE = 16;
	const int FIREARM_ATTRIBUTE_LABEL_SIZE = 24;
	const int FIREARM_ATTRIBUTE_AMOUNT_DECIMAL = 1;
	const int NAVIGATION_LABEL_SIZE = 48;

	const std::unordered_map<UIElementIndex, std::string> FIREARM_UPGRADE_LABEL_MAP = {
		{ UIElementIndex::Firearm_Main_Upgrade_Damage, "Damage" },
		{ UIElementIndex::Firearm_Main_Upgrade_CriticalDamage, "Critical Damage" },
		{ UIElementIndex::Firearm_Main_Upgrade_Firerate, "Firerate" },
		{ UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity, "Magazine Capacity" },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_ELEMENT_POSITION_MAP = {
		{ UIElementIndex::Shop_Background, Vector2(136.0f, 49.0f) },
		{ UIElementIndex::Shop_Navigation_Firearm, Vector2(170.0f, 80.0f) },
		{ UIElementIndex::Shop_Navigation_Melee, Vector2(490.0f, 80.0f) },
		{ UIElementIndex::Shop_Navigation_Utility, Vector2(810.0f, 80.0f) },
		{ UIElementIndex::Firearm_Main_Upgrade_Damage, Vector2(200.0f, 230.0f) },
		{ UIElementIndex::Firearm_Main_Upgrade_CriticalDamage, Vector2(475.0f, 230.0f) },
		{ UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity, Vector2(200.0f, 430.0f) },
		{ UIElementIndex::Firearm_Main_Upgrade_Firerate, Vector2(475.0f, 430.0f) },
		{ UIElementIndex::Firearm_Main_InfoBoard, Vector2(750.0f, 200.0f) },
		{ UIElementIndex::Firearm_Main_GunViewport, Vector2(765.0f, 224.0f) },
		{ UIElementIndex::Firearm_Main_Attribute_Content, Vector2(775.0f, 395.0f) },
		{ UIElementIndex::Firearm_Main_GunLabel, Vector2(862.0f, 230.0f) },
		{ UIElementIndex::Firearm_Main_Attribute_Frame, Vector2(750.0f, 200.0f) },
		{ UIElementIndex::Firearm_SelectionGrid, Vector2(150.0f, 160.0f) },
		{ UIElementIndex::Utility_ItemSelectionGrid, Vector2(170.0f, 205.0f) },
		{ UIElementIndex::Utility_InfoBoard, Vector2(757.0f, 205.0f) },
		{ UIElementIndex::Utility_BuyButton, Vector2(853.0f, 583.0f) },
		{ UIElementIndex::Utility_ItemViewport, Vector2(770.0f, 220.0f) },
		{ UIElementIndex::Utility_MoneyIcon, Vector2(865.0f, 590.0f) },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_ELEMENT_SCALE_MAP = {
		{ UIElementIndex::Firearm_Main_GunLabel, Vector2(127.0f, 19.0f) },
	};
	const std::unordered_map<UIElementIndex, Vector2> UI_ELEMENT_OFFSET_MAP = {
		{ UIElementIndex::Utility_MoneyLabel, Vector2(82.0f, 0.0f) },
		{ UIElementIndex::Utility_ItemLabel, Vector2(0.0f, -38.0f) },
	};
	const std::unordered_map<UIElementIndex, std::string> UI_LABEL_MAP = {
		{ UIElementIndex::Shop_Navigation_Firearm_Label, "Firearm" },
		{ UIElementIndex::Shop_Navigation_Melee_Label, "Melee" },
		{ UIElementIndex::Shop_Navigation_Utility_Label, "Utility" },
		{ UIElementIndex::Firearm_Main_Upgrade_Damage, "Damage" },
		{ UIElementIndex::Firearm_Main_Upgrade_CriticalDamage, "Critical Damage" },
		{ UIElementIndex::Firearm_Main_Upgrade_Firerate, "Firerate" },
		{ UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity, "Magazine Capacity" },
	};
	const std::unordered_map<UIElementIndex, std::string> UPGRADE_DESCRIPTION_PREFIX_MAP = {
		{ UIElementIndex::Firearm_Main_Upgrade_Damage, "Increase damage dealt by " },
		{ UIElementIndex::Firearm_Main_Upgrade_CriticalDamage, "Increase critical damage by " },
		{ UIElementIndex::Firearm_Main_Upgrade_Firerate, "Firerate increase by " },
		{ UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity, "Magazine capacity increases by " },
	};
	const std::unordered_map<UIElementIndex, std::string> UPGRADE_DESCRIPTION_SUFFIX_MAP = {
		{ UIElementIndex::Firearm_Main_Upgrade_Damage, "%." },
		{ UIElementIndex::Firearm_Main_Upgrade_CriticalDamage, "%." },
		{ UIElementIndex::Firearm_Main_Upgrade_Firerate, "%." },
		{ UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity, "%." },
	};
	const std::unordered_map<UIElementIndex, int> UI_FONT_SIZE_MAP = {
		{ UIElementIndex::Shop_Navigation_Firearm_Label, 48 },
		{ UIElementIndex::Shop_Navigation_Melee_Label, 48 },
		{ UIElementIndex::Shop_Navigation_Utility_Label, 48 },
		{ UIElementIndex::Firearm_Main_GunLabel, 16 },
		{ UIElementIndex::Utility_MoneyLabel, 24 },
		{ UIElementIndex::Utility_ItemLabel, 24 },
	};
	const std::unordered_map<FirearmAttributeIndex, UIElementIndex> UPGRADE_INDEX_BY_ATTRIBUTE_MAP = {
		{ FirearmAttributeIndex::Damage, UIElementIndex::Firearm_Main_Upgrade_Damage },
		{ FirearmAttributeIndex::CriticalDamage, UIElementIndex::Firearm_Main_Upgrade_CriticalDamage },
		{ FirearmAttributeIndex::Firerate, UIElementIndex::Firearm_Main_Upgrade_Firerate },
		{ FirearmAttributeIndex::MagazineCapacity, UIElementIndex::Firearm_Main_Upgrade_MagazineCapacity },
	};
	const std::unordered_map<ShopMenuIndex, UIElementIndex> NAVIGATION_INDEX_BY_SHOP_INDEX_MAP = {
		{ ShopMenuIndex::Firearm_Main, UIElementIndex::Shop_Navigation_Firearm },
		{ ShopMenuIndex::Firearm_Selection, UIElementIndex::Shop_Navigation_Firearm },
		{ ShopMenuIndex::Melee, UIElementIndex::Shop_Navigation_Melee },
		{ ShopMenuIndex::Utility, UIElementIndex::Shop_Navigation_Utility },
	};
	const std::string FIREARM_ATTRIBUTE_FRAME_PATH = "./Asset/Attribute_Frame.png";

	const Vector2 FIREARM_ATTRIBUTE_FRAME_POSITION = Vector2(750.0f, 200.0f);
	const Vector2 GUN_VIEWPORT_POSITION = Vector2(765.0f, 224.0f);


	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static Shop* instance;

	bool showShop;
	std::unordered_map<FirearmAttributeIndex, FirearmUpgrade*> firearmUpgradeMap;
	std::unordered_map<UIElementIndex, GameObject*> uiElementMap;
	Firearm* currentFirearm;
	ItemIndex currentItemIndex;
	ShopMenuIndex currentMenuIndex;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void Show();
	void Hide();
	void ShowCurrentMenu();
	void HideCurrentMenu();
	void InitializeUI();
	void InitializeUpgrades();
	void SwitchMenu(ShopMenuIndex targetMenuIndex);
	void UpdateAttributeList();
	UIElementIndex GetUIElementIndex(ShopMenuIndex shopMenuIndex);

public:

	Shop();
	void Update() override;
	void BuyUpgrade(FirearmAttributeIndex attribute);
	void SelectFirearm(Firearm* firearm);
	void SelectItem(ItemIndex itemIndex);
	void BuyItem();
	ItemIndex GetSelectedItem() const;
	static Shop* Instance();

};