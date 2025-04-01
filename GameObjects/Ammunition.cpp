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
/// STATIC FIELDS
/// ----------------------------------

const std::unordered_map<AmmunitionID, ItemIndex> Ammunition::AMMO_ITEM_INDEX_MAP = {
	{ AmmunitionID::Slug, ItemIndex::Ammo_Slug },
	{ AmmunitionID::Nine_Mil, ItemIndex::Ammo_9mm },
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Ammunition::Ammunition(AmmunitionID initAmmunitionID, int amount) : Item(AMMO_ITEM_INDEX_MAP.at(initAmmunitionID), amount) {

	ammunitionID = initAmmunitionID;

}

void Ammunition::Equip() {}

void Ammunition::Dequip() {}

bool Ammunition::TryAddToStack(int amount) {

	currentStack += amount;

	std::vector<Firearm*> firearmList = Player::Instance()->GetFirearmList();

	for (auto it = firearmList.begin(); it != firearmList.end(); it++) {

		if (ammunitionID == Firearm::BASE_FIREARM_INFO_MAP.at((*it)->GetIndex()).ammunitionID) {

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

AmmunitionID Ammunition::GetAmmunitionID() const { return ammunitionID; }