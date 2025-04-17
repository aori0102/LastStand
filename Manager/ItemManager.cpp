/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <ItemManager.h>

#include <exception>

#include <Ammunition.h>
#include <Consumable.h>
#include <Firearm.h>
#include <Item.h>
#include <MediaManager.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

ItemManager* ItemManager::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void ItemManager::InitializeItemInfo() {

	itemInfoMap = {
		{ ItemIndex::None, {} },
		{ ItemIndex::MedKit, {
			.price = 40,
			.shopStack = 1,
			.name = "Med Kit",
			.iconClip = { 7, 139, 48, 38 },
		} },
		{ ItemIndex::Pistol_M1911, {
			.price = 230,
			.shopStack = 0,
			.name = "M1911",
			.iconClip = { 73, 145, 48, 34 },
		} },
		{ ItemIndex::Shotgun_Beretta1301, {
			.price = 3900,
			.shopStack = 1,
			.name = "Beretta 1301 Tactical",
			.iconClip = { 135, 132, 55, 58 },
		} },
		{ ItemIndex::Rifle_M4, {
			.price = 2100,
			.shopStack = 1,
			.name = "M4",
			.iconClip = { 321, 129, 62, 62 },
		} },
		{ ItemIndex::Ammo_Slug, {
			.price = 40,
			.shopStack = 8,
			.name = "Slug",
			.iconClip = { 206, 144, 36, 27 },
		} },
		{ ItemIndex::Ammo_9mm, {
			.price = 25,
			.shopStack = 30,
			.name = "9mm",
			.iconClip = { 265, 145, 38, 24 },
		} },
		{ ItemIndex::Ammo_556, {
			.price = 60,
			.shopStack = 30,
			.name = "5.56 NATO",
			.iconClip = { 393, 145, 38, 24 },
		} },
	};

}

ItemManager::ItemManager() {

	if (instance)
		throw std::exception("Item Manager can only have one instance!");

	instance = this;

	InitializeItemInfo();

}

ItemManager::~ItemManager() {

	itemInfoMap.clear();

	instance = nullptr;

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

int ItemManager::GetItemShopStack(ItemIndex itemIndex) { return itemInfoMap.at(itemIndex).shopStack; }

std::string ItemManager::GetItemName(ItemIndex itemIndex) { return itemInfoMap.at(itemIndex).name; }

Item* ItemManager::CreateItem(ItemIndex itemIndex, int amount) {

	Item* product = nullptr;

	switch (itemIndex) {

	case ItemIndex::Pistol_M1911:

		product = GameObject::Instantiate<Pistol>("Pistol");
		break;

	case ItemIndex::Shotgun_Beretta1301:

		product = GameObject::Instantiate<Shotgun>("Shotgun");
		break;

	case ItemIndex::Rifle_M4:

		product = GameObject::Instantiate<Rifle>("Rifle");
		break;

	case ItemIndex::MedKit:

		product = GameObject::Instantiate<Consumable>("Med Kit");
		break;

	case ItemIndex::Ammo_Slug:

		product = GameObject::Instantiate<Ammunition>("Slug");
		break;

	case ItemIndex::Ammo_9mm:

		product = GameObject::Instantiate<Ammunition>("9mm Ammo");
		break;

	case ItemIndex::Ammo_556:

		product = GameObject::Instantiate<Ammunition>("5.56 Ammo");
		break;

	}

	if (product) {

		product->SetIndex(itemIndex);
		product->SetAmount(amount);

	}

	return product;

}

ItemManager* ItemManager::Instance() { return instance; }