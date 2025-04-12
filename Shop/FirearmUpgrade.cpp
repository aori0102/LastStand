/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <FirearmUpgrade.h>

#include <DataManager.h>
#include <Firearm.h>
#include <ItemManager.h>
#include <Shop.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void FirearmUpgrade::SaveUpgradeData() {

	DataManager::Instance()->playerSaveData->firearmUpgradeProgress[firearmIndex][attribute]
		= currentProgress;

}

FirearmUpgrade::FirearmUpgrade(ItemIndex initFirearmIndex, FirearmAttributeIndex initAttribute, bool initSortDescending) {

	currentProgress = 0;
	sortDescending = initSortDescending;
	currentUpgrade = nullptr;
	tailNode = nullptr;
	attribute = initAttribute;
	firearmIndex = initFirearmIndex;

}

FirearmUpgrade::~FirearmUpgrade() {

	SaveUpgradeData();

	while (currentUpgrade) {

		auto next = currentUpgrade->next;

		delete currentUpgrade;
		currentUpgrade = next;

	}

}

void FirearmUpgrade::AddUpgrade(UpgradeNode* newUpgrade) {

	if (!currentUpgrade) {

		currentUpgrade = newUpgrade;
		tailNode = newUpgrade;
		return;

	}

	if (sortDescending && newUpgrade->cost > currentUpgrade->cost)
		throw std::exception("Invalid upgrade amount order");
	else if (!sortDescending && newUpgrade->cost < currentUpgrade->cost)
		throw std::exception("Invalid upgrade amount order");

	tailNode->next = newUpgrade;
	tailNode = newUpgrade;

	// If this upgrade progress tier is lower than saved one,
	// modify the attribute and delete the node
	if (currentProgress < DataManager::Instance()->playerSaveData->firearmUpgradeProgress.at(firearmIndex).at(attribute))
		UpgradeNext();

}

void FirearmUpgrade::UpgradeNext() {

	if (!currentUpgrade || firearmIndex == ItemIndex::None)
		return;

	Firearm::ModifyAttributeMultiplier(firearmIndex, attribute, currentUpgrade->amount);

	UpgradeNode* nextUpgrade = currentUpgrade->next;
	delete currentUpgrade;
	currentUpgrade = nextUpgrade;

	currentProgress++;
	if (currentProgress > DataManager::Instance()->playerSaveData->firearmUpgradeProgress.at(firearmIndex).at(attribute))
		DataManager::Instance()->playerSaveData->firearmUpgradeProgress.at(firearmIndex)[attribute] = currentProgress;

}

int FirearmUpgrade::NextUpgradeCost() {

	if (currentUpgrade)
		return currentUpgrade->cost;

	return INT_MAX;

}

float FirearmUpgrade::NextUpgradeAmount() {

	if (currentUpgrade)
		return currentUpgrade->amount;

	return -FLT_MAX;

}