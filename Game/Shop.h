#pragma once

#include <GameComponent.h>
#include <vector>
#include <Firearm.h>
#include <functional>
#include <RenderManager.h>
#include <string>

class Player;
struct ButtonUIGroup;

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

	};
	unordered_map<Firearm::Attribute, FirearmUpgrade*> firearmUpgradeMap;

	// Player to control interaction
	Player* linkedPlayer;

	// Shop items

	// UI elements
	// General
	GameObject* background;
	const string BACKGROUND_PATH = "./Asset/Shop_Background.png";

	GameObject* buyButton;
	GameObject* buyButtonLabel;

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
	const int NAVIGATION_LABEL_SIZE = 32;

	// Firearm upgrade
	GameObject* damageUpgradeButton;
	GameObject* damageUpgradeButtonLabel;
	GameObject* damageUpgradeButtonAmountLabel;

	GameObject* reloadTimeUpgradeButton;
	GameObject* reloadTimeUpgradeButtonLabel;
	GameObject* reloadTimeUpgradeButtonAmountLabel;

	GameObject* ammoCapacityUpgradeButton;
	GameObject* ammoCapacityUpgradeButtonLabel;
	GameObject* ammoCapacityUpgradeButtonAmountLabel;

	const float UPGRADE_VERTICAL_MARGIN = 30.0f;

	// Control
	bool showShop;
	ShopMenuIndex shopMenuIndex;
	void Show();
	void Hide();

	void RenderFirearmMenu();
	void ShowCurrentMenu();
	void HideCurrentMenu();

	void InitializeUI();
	void InitializeUpgrades();

	void BuyUpgrade(Firearm::Attribute attribute);

public:

	Shop(Player* initPlayer);
	void Update() override;

};