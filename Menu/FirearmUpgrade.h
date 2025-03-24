#pragma once

#include <functional>
#include <string>

class Firearm;
class UpgradeNode;
enum class FirearmAttributeIndex;

class FirearmUpgrade {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool sortDescending;
	UpgradeNode* currentUpgrade;
	UpgradeNode* tailNode;
	FirearmAttributeIndex attribute;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	FirearmUpgrade(FirearmAttributeIndex initAttribute, bool initSortDescending = false);

	void AddUpgrade(UpgradeNode* newNode);
	void UpgradeNext(Firearm* firearm);
	int NextUpgradeCost();
	float NextUpgradeAmount();

};