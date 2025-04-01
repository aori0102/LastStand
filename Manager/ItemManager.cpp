﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
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
			.price = 2300,
			.shopStack = 0,
			.name = "Beretta 1301 Tactical",
			.iconClip = { 135, 132, 55, 58 },
		} },
		{ ItemIndex::Ammo_Slug, {
			.price = 25,
			.shopStack = 8,
			.name = "Slug",
			.iconClip = { 206, 144, 36, 27 },
		} },
		{ ItemIndex::Ammo_9mm, {
			.price = 40,
			.shopStack = 30,
			.name = "9mm",
			.iconClip = { 265, 145, 38, 24 },
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

	switch (itemIndex) {

	case ItemIndex::Pistol_M1911:

		return new Pistol(itemIndex);

	case ItemIndex::Shotgun_Beretta1301:

		return new Shotgun(itemIndex);

	case ItemIndex::MedKit: {

		Consumable* medkit = new Consumable(itemIndex, amount);
		medkit->health = 30.0f;
		medkit->stackable = 7.0f;

		return medkit;

	}

	case ItemIndex::Ammo_Slug: {

		Ammunition* slug = new Ammunition(AmmunitionID::Slug, amount);

		return slug;

	}

	case ItemIndex::Ammo_9mm: {

		Ammunition* ammo = new Ammunition(AmmunitionID::Nine_Mil, amount);

		return ammo;

	}

	}

}

ItemManager* ItemManager::Instance() { return instance; }