#pragma once

#include <Utils.h>
#include <string>
#include <GameComponent.h>

enum class FirearmAttributeIndex;

class FirearmUpgradeUIGroup : public GameObject {

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

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float upgradeAmount;
	int descriptionDecimalPlace;
	std::string descriptionPrefix;
	std::string descriptionSuffix;
	FirearmAttributeIndex firearmAttributeIndex;
	
	GameObject* upgradeLabel;
	GameObject* upgradeDescription;
	GameObject* upgradeCost;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void UpdateDescription();
	void Show();
	void Hide();

public:

	FirearmUpgradeUIGroup();

	void SetAttribute(FirearmAttributeIndex firearmAttributeIndex);
	void SetLabel(std::string label);
	void SetDescriptionPrefix(std::string prefix);
	void SetDescriptionSuffix(std::string suffix);
	void SetAmount(float amount, int decimalPlace);
	void SetCost(int amount);
	void SetPosition(Vector2 positionInSDL);

};