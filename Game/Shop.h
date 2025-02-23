#pragma once

#include <GameComponent.h>
#include <vector>
#include <Item.h>
#include <functional>
#include <RenderManager.h>

class Player;

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
	GameObject* background;

	GameObject* buyButton;
	GameObject* buyButtonLabel;

	GameObject* firearmButton;
	GameObject* firearmButtonLabel;

	GameObject* meleeButton;
	GameObject* meleeButtonLabel;

	GameObject* utilityButton;
	GameObject* utilityButtonLabel;

	GameObject* damageUpgradeButton;
	GameObject* damageUpgradeButtonLabel;
	GameObject* damageUpgradeButtonAmountLabel;

	GameObject* reloadTimeUpgradeButton;
	GameObject* reloadTimeUpgradeButtonLabel;
	GameObject* reloadTimeUpgradeButtonAmountLabel;

	GameObject* ammoCapacityUpgradeButton;
	GameObject* ammoCapacityUpgradeButtonLabel;
	GameObject* ammoCapacityUpgradeButtonAmountLabel;

	// Control
	bool showShop;
	ShopMenuIndex shopMenuIndex;
	void Show();
	void Hide();

	void RenderFirearmMenu();
	void ShowFirearmMenu();
	void HideFirearmMenu();

	void InitializeUI();
	void InitializeUpgrades();

	void BuyUpgrade(Firearm::Attribute attribute);

public:

	Shop(Player* initPlayer);
	void Update() override;

};