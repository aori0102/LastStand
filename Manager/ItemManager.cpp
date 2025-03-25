/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <ItemManager.h>

#include <exception>

#include <Consumable.h>
#include <Item.h>
#include <Firearm.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

ItemManager* ItemManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

ItemManager::ItemManager() {

	if (instance)
		throw std::exception("Item Manager can only have one instance!");

	instance = this;

}

ItemManager* ItemManager::Instance() { return instance; }

Item* ItemManager::CreateItem(ItemIndex itemIndex, int amount) {

	switch (itemIndex) {

	case ItemIndex::Pistol_M1911:

		return new Pistol(itemIndex);

	case ItemIndex::Shotgun_Beretta1301:

		return new Shotgun(itemIndex);

	case ItemIndex::MedKit: {

		Consumable* medkit = new Consumable(itemIndex);
		medkit->health = 30.0f;
		medkit->stackable = 7.0f;

		return medkit;

	}

	}

	return nullptr;

}