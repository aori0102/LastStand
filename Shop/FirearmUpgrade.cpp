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

	sortDescending = initSortDescending;
	currentNode = nullptr;
	tailNode = nullptr;
	headNode = nullptr;
	attribute = initAttribute;
	firearmIndex = initFirearmIndex;
	currentProgress = 0;
	savedProgress = DataManager::Instance()->playerSaveData->firearmUpgradeProgress.at(firearmIndex).at(attribute);

}

FirearmUpgrade::~FirearmUpgrade() {

	SaveUpgradeData();

	while (currentNode) {

		auto next = currentNode->next;

		delete currentNode;
		currentNode = next;

	}

}

void FirearmUpgrade::AddUpgrade(UpgradeNode* newUpgrade) {

	if (currentProgress < savedProgress) {

		Firearm::ModifyAttributeMultiplier(firearmIndex, attribute, newUpgrade->amount);
		delete newUpgrade;
		currentProgress++;
		return;

	}

	if (!headNode) {

		headNode = newUpgrade;
		currentNode = newUpgrade;
		tailNode = newUpgrade;
		return;

	}

	if (sortDescending && newUpgrade->cost > currentNode->cost)
		throw std::exception("Invalid upgrade amount order");
	else if (!sortDescending && newUpgrade->cost < currentNode->cost)
		throw std::exception("Invalid upgrade amount order");

	tailNode->next = newUpgrade;
	tailNode = newUpgrade;

}

void FirearmUpgrade::UpgradeNext() {

	if (!currentNode || firearmIndex == ItemIndex::None)
		return;

	Firearm::ModifyAttributeMultiplier(firearmIndex, attribute, currentNode->amount);

	UpgradeNode* nextUpgrade = currentNode->next;
	delete currentNode;
	currentNode = nextUpgrade;

	currentProgress++;

}

void FirearmUpgrade::ClearUpgrade() {

	currentNode = headNode;

	currentNode = nullptr;
	tailNode = nullptr;

	currentProgress = 0;
	savedProgress = 0;

}

int FirearmUpgrade::NextUpgradeCost() {

	if (currentNode)
		return currentNode->cost;

	return INT_MAX;

}

float FirearmUpgrade::NextUpgradeAmount() {

	if (currentNode)
		return currentNode->amount;

	return -FLT_MAX;

}