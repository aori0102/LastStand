/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <FirearmUpgrade.h>

#include <Firearm.h>
#include <Shop.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

FirearmUpgrade::FirearmUpgrade(FirearmAttributeIndex initAttribute, bool initSortDescending) {

	sortDescending = initSortDescending;
	currentUpgrade = nullptr;
	tailNode = nullptr;
	attribute = initAttribute;

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

}

void FirearmUpgrade::UpgradeNext(Firearm* firearm) {

	if (!currentUpgrade || !firearm)
		return;
	
	firearm->ModifyAttributeMultiplier(attribute, currentUpgrade->amount);

	std::cout << "Upgrading to next tier. New amount: " << currentUpgrade->amount << " for " << currentUpgrade->cost << " cost" << std::endl;

	UpgradeNode* nextUpgrade = currentUpgrade->next;
	delete currentUpgrade;
	currentUpgrade = nextUpgrade;

}

int FirearmUpgrade::NextUpgradeCost() {

	if (currentUpgrade)
		return currentUpgrade->cost;

	return INT_MAX;

}

float FirearmUpgrade::NextUpgradeAmount() {

	if (currentUpgrade)
		return currentUpgrade->amount;

	return 0.0f;

}