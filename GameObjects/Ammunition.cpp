/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Ammunition.h>

#include <vector>

#include <Firearm.h>
#include <Item.h>
#include <ItemManager.h>
#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Ammunition::SetAmmunitionItemIndex(ItemIndex initItemIndex) {

	if (!ItemManager::Instance()->IsIndexOfType<Ammunition>(initItemIndex))
		throw std::exception("Invalid Item ID for ammunition!");

	SetIndex(initItemIndex);

}

void Ammunition::Equip() {}

void Ammunition::Dequip() {}

bool Ammunition::TryAddToStack(int amount) {

	currentStack += amount;

	std::vector<Firearm*> firearmList = Player::Instance()->GetFirearmList();

	for (auto it = firearmList.begin(); it != firearmList.end(); it++) {

		if (GetIndex() == Firearm::BASE_FIREARM_INFO_MAP.at((*it)->GetIndex()).ammunitionItemIndex) {

			// Update reserve ammo of firearm that uses this ammo
			(*it)->UpdateReserveLabel();
			break;

		}

	}

	return true;

}

bool Ammunition::TryRemoveFromStack(int amount) {

	if (!IsSufficient(amount))
		return false;

	currentStack -= amount;

	return true;

}

bool Ammunition::TryUse() { return false; }