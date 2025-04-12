#pragma once

#include <functional>
#include <string>

class UpgradeNode;
enum class FirearmAttributeIndex;
enum class ItemIndex;

class FirearmUpgrade {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool sortDescending;
	int currentProgress;
	UpgradeNode* currentUpgrade;
	UpgradeNode* tailNode;
	FirearmAttributeIndex attribute;
	ItemIndex firearmIndex;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void SaveUpgradeData();

public:

	FirearmUpgrade(ItemIndex initFirearmIndex, FirearmAttributeIndex initAttribute, bool initSortDescending = false);
	~FirearmUpgrade();
	void AddUpgrade(UpgradeNode* newNode);
	void UpgradeNext();
	int NextUpgradeCost();
	float NextUpgradeAmount();

};