/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
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

class Shop : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

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

		/// ----------------------------------
		/// FIELDS
		/// ----------------------------------

	private:

		std::function<bool(float, float)> betterNode;

		UpgradeNode* currentUpgrade;
		UpgradeNode* tailNode;
		FirearmAttributeIndex attribute;

	public:

		std::string name;
		std::string description;

		/// ----------------------------------
		/// METHODS
		/// ----------------------------------

	public:

		FirearmUpgrade(FirearmAttributeIndex initAttribute, std::function<bool(float, float)> initBetterNode = [](float newUp, float oldUp) { return newUp > oldUp; });

		void AddUpgrade(UpgradeNode* newNode);
		void UpgradeNext(Firearm* firearm);
		int NextUpgradeCost();
		float NextUpgradeAmount();

	};

	class FirearmUpgradeUIGroup {

		/// ----------------------------------
		/// STRUCTURES AND CONSTANTS
		/// ----------------------------------

	private:

		static const int UPGRADE_LABEL_SIZE;
		static const int UPGRADE_DESCRIPTION_SIZE;
		static const int UPGADE_COST_SIZE;
		static const float UPGRADE_LABEL_OFFSET_Y;
		static const float UPGRADE_COST_OFFSET_Y;
		static const std::string COST_PREFIX;
		static const std::string OBJECT_NAME_SUFFIX;
		static const Color UPGRADE_LABEL_COLOR;
		static const Color UPGRADE_ATTRIBUTE_COLOR;

		/// ----------------------------------
		/// FIELDS
		/// ----------------------------------

	private:

		GameObject* labelObject;
		GameObject* buttonObject;
		GameObject* descriptionObject;
		GameObject* amountObject;
		GameObject* costObject;

		Shop* linkedShop;
		FirearmAttributeIndex assignedAttribute;

	public:

		float amount;
		float descriptionMargin;
		int cost;
		int amountDecimalPlace;
		std::string label;
		std::string descriptionPrefix;
		std::string descriptionSuffix;

		/// ----------------------------------
		/// METHODS
		/// ----------------------------------

	public:

		FirearmUpgradeUIGroup(Shop* initShop, FirearmAttributeIndex initAttribute);

		void Update(Vector2 framePosition);
		void Show();
		void Hide();

	};

	class FirearmAttributeInfoGroup {

		/// ----------------------------------
		/// STRUCTURES AND CONSTANTS
		/// ----------------------------------

	private:

		static const std::string OBJECT_NAME_SUFFIX;

	private:

		/// ----------------------------------
		/// FIELDS
		/// ----------------------------------

		GameObject* labelObject;
		GameObject* amountLabelObject;

	public:

		int labelSize;
		int amountDecimalPlace;
		float amount;
		std::string label;

		Color labelColor;

		/// ----------------------------------
		/// METHODS
		/// ----------------------------------

	public:

		FirearmAttributeInfoGroup();

		void Update(Vector2 labelPosition, float amountLabelLeft);
		void Show();
		void Hide();

	};

	// Upgrade buttons preset
	static const float UPGRADE_DESCRIPTION_MARGIN;
	static const std::unordered_map<FirearmAttributeIndex, std::string> FIREARM_UPGRADE_LABEL_MAP;
	static const std::unordered_map<FirearmAttributeIndex, Vector2> FIREARM_UPGRADE_POSITION;
	static const std::unordered_map<FirearmAttributeIndex, std::string> FIREARM_UPGRADE_DESCRIPTION_PREFIX_MAP;
	static const std::unordered_map<FirearmAttributeIndex, std::string> FIREARM_UPGRADE_DESCRIPTION_SUFFIX_MAP;

	// Navigation buttons preset
	static const int NAVIGATION_LABEL_SIZE;
	static const std::unordered_map<ShopMenuIndex, std::string> MENU_NAVIGATION_LABEL_MAP;
	static const std::unordered_map<ShopMenuIndex, Vector2> MENU_NAVIGATION_POSITION;

	// Firearm attribute preset
	static const float FIREARM_ATTRIBUTE_VALUE_LEFT;
	static const int FIREARM_ATTRIBUTE_LABEL_SIZE;
	static const int FIREARM_ATTRIBUTE_AMOUNT_DECIMAL;
	static const std::string FIREARM_ATTRIBUTE_FRAME_PATH;
	static const std::unordered_map<FirearmAttributeIndex, Vector2> FIREARM_ATTRIBUTE_POSITION_MAP;
	static const std::unordered_map<FirearmAttributeIndex, std::string> FIREARM_ATTRIBUTE_LABEL_MAP;
	static const Vector2 FIREARM_ATTRIBUTE_FRAME_POSITION;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<FirearmAttributeIndex, FirearmUpgradeUIGroup*> firearmUpgradeUIGroupMap;
	std::unordered_map<FirearmAttributeIndex, FirearmAttributeInfoGroup*> firearmAttributeInfoMap;
	std::unordered_map<ShopMenuIndex, ButtonUIGroup*> menuNavigationButtonMap;
	std::unordered_map<FirearmAttributeIndex, FirearmUpgrade*> firearmUpgradeMap;

	GameObject* firearmAttributeFrame;
	GameObject* background;
	Player* linkedPlayer;

	// Control
	bool showShop;

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

public:

	Shop(Player* initPlayer);

	void Update() override;

	void BuyUpgrade(FirearmAttributeIndex attribute);

};