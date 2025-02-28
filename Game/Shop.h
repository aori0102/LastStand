#pragma once

#include <GameComponent.h>
#include <vector>
#include <Firearm.h>
#include <functional>
#include <RenderManager.h>
#include <string>
#include <Type.h>

class Player;
struct ButtonUIGroup;
class Shop;

class FirearmUpgradeUIGroup {

private:

	const std::string UPGRADE_SLOT_PATH = "./Asset/Upgrade_Slot.png";
	const std::string COST_PREFIX = "Cost: ";
	const std::string OBJECT_NAME_SUFFIX = "_UpgradeButton";
	const int UPGRADE_LABEL_SIZE = 24;
	const int UPGRADE_DESCRIPTION_SIZE = 14;
	const int UPGADE_COST_SIZE = 14;
	const float UPGRADE_LABEL_OFFSET_Y = 15.0f;
	const float UPGRADE_COST_OFFSET_Y = 130.0f;
	const Color UPGRADE_LABEL_COLOR = Color::WHITE;
	const Color UPGRADE_ATTRIBUTE_COLOR = Color::GREEN;

	GameObject* labelObject;
	GameObject* buttonObject;
	GameObject* descriptionObject;
	GameObject* amountObject;
	GameObject* costObject;

	Shop* linkedShop;
	Firearm::Attribute assignedAttribute;

public:

	FirearmUpgradeUIGroup(Shop* initShop, Firearm::Attribute initAttribute);

	std::string label;
	std::string descriptionPrefix;
	std::string descriptionSuffix;
	float amount;
	float descriptionMargin;
	int cost;
	int amountDecimalPlace;

	void Update(Vector2 framePosition);
	void Show();
	void Hide();

};

class FirearmAttributeInfoGroup {

private:

	GameObject* labelObject;
	GameObject* amountLabelObject;

	const std::string OBJECT_NAME_SUFFIX = "_InfoGroup";

public:

	FirearmAttributeInfoGroup();

	Color labelColor;
	std::string label;
	int labelSize;
	int amountDecimalPlace;
	float amount;

	void Update(Vector2 labelPosition, float amountLabelLeft);
	void Show();
	void Hide();

};

class Shop : public GameObject {

private:

	// For menu navigation
	enum class ShopMenuIndex {

		Firearm,
		Melee,
		Utility

	};

	// Upgrades
	struct UpgradeNode {

		int cost;
		float amount;
		UpgradeNode* next;

		UpgradeNode(int initCost, float initAmount)
			: cost(initCost), amount(initAmount), next(nullptr) {}

	};

	class FirearmUpgrade {

	private:

		UpgradeNode* currentUpgrade;
		UpgradeNode* tailNode;
		Firearm::Attribute attribute;
		function<bool(float, float)> betterNode;

	public:

		string name;
		string description;

		FirearmUpgrade(Firearm::Attribute initAttribute, function<bool(float, float)> initBetterNode = [](float newUp, float oldUp) { return newUp > oldUp; });

		void AddUpgrade(UpgradeNode* newNode);
		void UpgradeNext(Firearm* firearm);
		int NextUpgradeCost();
		float NextUpgradeAmount();

	};
	unordered_map<Firearm::Attribute, FirearmUpgrade*> firearmUpgradeMap;

	// Player to control interaction
	Player* linkedPlayer;

	// Shop items

	// ---------------------------------------------------------------------------------
	// 
	// U I   E L E M E N T S
	// 
	// ---------------------------------------------------------------------------------

	// General
	GameObject* background;
	const string BACKGROUND_PATH = "./Asset/Shop_Background.png";

	// Navigation
	std::unordered_map<ShopMenuIndex, ButtonUIGroup*> menuNavigationButtonMap;
	const std::unordered_map<ShopMenuIndex, const std::string> MENU_NAVIGATION_LABEL_MAP = {
		{ ShopMenuIndex::Firearm, "Firearm" },
		{ ShopMenuIndex::Melee, "Melee" },
		{ ShopMenuIndex::Utility, "Utility" }
	};
	const std::unordered_map<ShopMenuIndex, Vector2> MENU_NAVIGATION_POSITION = {
		{ ShopMenuIndex::Firearm, Vector2(170.0f, 80.0f) },
		{ ShopMenuIndex::Melee, Vector2(490.0f, 80.0f) },
		{ ShopMenuIndex::Utility, Vector2(810.0f, 80.0f) }
	};
	const std::string NAVIGATION_UNSELECTED_PATH = "./Asset/Navigation_Button_Unselected.png";
	const std::string NAVIGATION_SELECTED_PATH = "./Asset/Navigation_Button_Selected.png";
	const int NAVIGATION_LABEL_SIZE = 48;

	// Firearm upgrade
	std::unordered_map<Firearm::Attribute, FirearmUpgradeUIGroup*> firearmUpgradeUIGroupMap;
	const std::unordered_map<Firearm::Attribute, const std::string> FIREARM_UPGRADE_LABEL_MAP = {
		{ Firearm::Attribute::Damage, "Damage" },
		{ Firearm::Attribute::ReloadTime, "Reload Time" },
		{ Firearm::Attribute::MaxAmmo, "Max Ammo" },
		{ Firearm::Attribute::CriticalChance, "Critical Chance" }
	};
	const std::unordered_map<Firearm::Attribute, Vector2> FIREARM_UPGRADE_POSITION = {
		{ Firearm::Attribute::Damage, Vector2(200.0f, 230.0f) },
		{ Firearm::Attribute::ReloadTime, Vector2(475.0f, 230.0f) },
		{ Firearm::Attribute::MaxAmmo, Vector2(200.0f, 430.0f) },
		{ Firearm::Attribute::CriticalChance, Vector2(475.0f, 430.0f) }
	};
	const std::unordered_map<Firearm::Attribute, std::string> FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP = {
		{ Firearm::Attribute::Damage, "Increase firearm damage by " },
		{ Firearm::Attribute::ReloadTime, "Reduce time take to reload to " },
		{ Firearm::Attribute::MaxAmmo, "Expand magazine, holding up to " },
		{ Firearm::Attribute::CriticalChance, "Increase critical chance by " }
	};
	const std::unordered_map<Firearm::Attribute, std::string> FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP = {
		{ Firearm::Attribute::Damage, " times." },
		{ Firearm::Attribute::ReloadTime, "s." },
		{ Firearm::Attribute::MaxAmmo, " rounds." },
		{ Firearm::Attribute::CriticalChance, " times." }
	};
	const float UPGRADE_DESCRIPTION_MARGIN = 40.0f;

	// Firearm attribute info
	GameObject* firearmAttributeFrame;
	const std::string FIREARM_ATTRIBUTE_FRAME_PATH = "./Asset/Attribute_Frame.png";
	const Vector2 FIREARM_ATTRIBUTE_FRAME_POSITION = Vector2(750.0f, 200.0f);
	const float FIREARM_ATTRIBUTE_VALUE_LEFT = 1075.0f;
	const int FIREARM_ATTRIBUTE_LABEL_SIZE = 24;
	const int FIREARM_ATTRIBUTE_AMOUNT_DECIMAL = 1;
	std::unordered_map<Firearm::Attribute, FirearmAttributeInfoGroup*> firearmAttributeInfoMap;
	const std::unordered_map<Firearm::Attribute, Vector2> FIREARM_ATTRIBUTE_POSITION_MAP = {
		{ Firearm::Attribute::Damage, Vector2(775.0f, 220.0f) },
		{ Firearm::Attribute::ReloadTime, Vector2(775.0f, 265.0f) },
		{ Firearm::Attribute::MaxAmmo, Vector2(775.0f, 310.0f) },
		{ Firearm::Attribute::CriticalChance, Vector2(775.0f, 355.0f) }
	};
	const std::unordered_map<Firearm::Attribute, std::string> FIREARM_ATTRIBUTE_LABEL_MAP = {
		{ Firearm::Attribute::Damage, "Damage" },
		{ Firearm::Attribute::ReloadTime, "Reload Time" },
		{ Firearm::Attribute::MaxAmmo, "Max Ammo" },
		{ Firearm::Attribute::CriticalChance, "Critical Chance" }
	};

	// Control
	bool showShop;
	ShopMenuIndex shopMenuIndex;
	void Show();
	void Hide();

	void ShowCurrentMenu();
	void HideCurrentMenu();

	void InitializeUI();
	void InitializeUpgrades();

public:

	Shop(Player* initPlayer);
	void Update() override;

	void BuyUpgrade(Firearm::Attribute attribute);

};