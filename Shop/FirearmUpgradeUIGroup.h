#pragma once

#include <Utils.h>
#include <string>
#include <GameComponent.h>

class UpgradeNode;
enum class FirearmAttributeIndex;

class FirearmUpgradeUIGroup : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const int UPGRADE_LABEL_SIZE;
	static const int UPGRADE_DESCRIPTION_SIZE;
	static const int UPGADE_COST_SIZE;
	static const int UPGADE_AMOUNT_DECIMAL;
	static const int NO_MORE_UPGRADE_FONT_SIZE;
	static const float UPGRADE_LABEL_OFFSET_Y;
	static const float UPGRADE_COST_OFFSET_Y;
	static const std::string COST_PREFIX;
	static const std::string NO_MORE_UPGRADE_MESSAGE;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool upgradeAvailable;
	float upgradeAmount;
	std::string descriptionPrefix;
	std::string descriptionSuffix;
	FirearmAttributeIndex firearmAttributeIndex;
	
	GameObject* frame;
	GameObject* upgradeLabel;
	GameObject* upgradeDescription;
	GameObject* upgradeCost;
	GameObject* noMoreUpgrade;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeUI();
	void UpdateDescription();
	void Show();
	void Hide();

public:

	FirearmUpgradeUIGroup();

	void SetAttribute(FirearmAttributeIndex firearmAttributeIndex);
	void SetLabel(std::string label);
	void SetDescriptionPrefix(std::string prefix);
	void SetDescriptionSuffix(std::string suffix);
	void SetPosition(Vector2 positionInSDL);
	void SetUpgrade(UpgradeNode* upgrade);

};