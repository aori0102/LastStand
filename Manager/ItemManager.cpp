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
#include <MediaManager.h>
#include <Texture.h>

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

	itemInfoMap = {
		{ ItemIndex::None, {} },
		{ ItemIndex::MedKit, {
			.iconClip = { 7, 7, 48, 38 },
			.price = 40,
			.name = "Med Kit",
		} },
		{ ItemIndex::Pistol_M1911, {
			.iconClip = { 71, 14, 33, 23 },
			.price = 230,
			.name = "M1911",
		} },
		{ ItemIndex::Shotgun_Beretta1301, {
			.iconClip = { 5, 59, 99, 26 },
			.price = 2300,
			.name = "Beretta 1301 Tactical",
		} },
	};

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

void ItemManager::LinkItemIcon(ItemIndex itemIndex, Image* out) {

	if (!out)
		return;

	auto it = itemInfoMap.find(itemIndex);
	if (it == itemInfoMap.end())
		throw std::exception("Item icon does not exist");

	out->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_ItemIcon), false);
	out->clip = it->second.iconClip;

}

int ItemManager::GetItemPrice(ItemIndex itemIndex) { return itemInfoMap.at(itemIndex).price; }

std::string ItemManager::GetItemName(ItemIndex itemIndex) { return itemInfoMap.at(itemIndex).name; }