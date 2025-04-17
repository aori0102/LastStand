#pragma once

#include <functional>
#include <string>

enum class FirearmAttributeIndex;
enum class ItemIndex;

class UpgradeNode {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	int cost;
	float amount;
	UpgradeNode* next;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

	UpgradeNode(int initCost, float initAmount)
		: cost(initCost), amount(initAmount), next(nullptr) {}

};

class FirearmUpgrade {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool sortDescending;
	int currentProgress;
	int savedProgress;
	UpgradeNode* currentNode;
	UpgradeNode* headNode;
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
	void ClearUpgrade();
	int NextUpgradeCost();
	float NextUpgradeAmount();
	UpgradeNode* GetNextUpgrade();

};