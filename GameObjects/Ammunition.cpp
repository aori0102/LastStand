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

	switch (initItemIndex) {

	case ItemIndex::Ammo_Slug:
	case ItemIndex::Ammo_9mm:
	case ItemIndex::Ammo_556:
		break;
	default:
		throw std::exception("Invalid ammunition ID");
	}

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

bool Ammunition::TryUse(Player* player) { return false; }