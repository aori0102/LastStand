/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Inventory.h>

#include <exception>

#include <Consumable.h>
#include <DataManager.h>
#include <Firearm.h>
#include <HotBar.h>
#include <InventoryUI.h>
#include <Item.h>
#include <ItemManager.h>
#include <Player.h>
#include <Shop.h>

const std::unordered_map<ItemIndex, int> Inventory::STARTER_KIT = {
	{ ItemIndex::Pistol_M1911, 10 },
	{ ItemIndex::Ammo_9mm, 80 },
};
Inventory* Inventory::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Inventory::Inventory() {

	if (instance)
		throw std::exception("Inventory can only have one instance!");

	instance = this;

	storage = {};

}

Inventory::~Inventory() {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		GameObject::Destroy(it->second);

	}

	storage.clear();

	instance = nullptr;

}

void Inventory::AddItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end() || !storage.at(itemIndex)) {
		// Item not found in inventory
		Item* newItem = ItemManager::Instance()->CreateItem(itemIndex, amount);

		storage[itemIndex] = newItem;

		if (ItemManager::Instance()->IsIndexOfType<Firearm>(itemIndex))
			Shop::Instance()->AddFirearmToUpgrade(newItem->ToType<Firearm>());

		if (!HotBar::Instance()->TryAddItem(itemIndex)) {

			// Add this to internal storage
			InventoryUI::Instance()->AddItemToInventory(itemIndex);

		}

	} else		// Item found in inventory
		(it_storage->second)->TryAddToStack(amount);

}

void Inventory::ToggleInventory() {

	InventoryUI::Instance()->IsActive() ? InventoryUI::Instance()->Disable() : InventoryUI::Instance()->Enable();

}

void Inventory::SaveInventory() {

	PlayerSaveData* playerSaveData = DataManager::Instance()->playerSaveData;

	playerSaveData->storage.clear();

	// Save items in inventory to data
	for (auto it = storage.begin(); it != storage.end(); it++)
		playerSaveData->storage[it->first] = (it->second)->GetCurrentStack();

}

void Inventory::LoadInventory() {

	if (DataManager::Instance()->playerSaveData->newSave) {

		for (auto it = STARTER_KIT.begin(); it != STARTER_KIT.end(); it++)
			AddItem(it->first, it->second);

	} else {

		std::unordered_map<ItemIndex, int> savedStorage = DataManager::Instance()->playerSaveData->storage;

		for (auto it = savedStorage.begin(); it != savedStorage.end(); it++)
			AddItem(it->first, it->second);

		savedStorage.clear();

	}

}

void Inventory::ResetInventory() {

	for (auto it = storage.begin(); it != storage.end(); it++)
		GameObject::Destroy(it->second);

	storage.clear();
	InventoryUI::Instance()->Reset();

	for (auto it = STARTER_KIT.begin(); it != STARTER_KIT.end(); it++)
		AddItem(it->first, it->second);

}

bool Inventory::IsSufficient(ItemIndex itemIndex, int amount) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->IsSufficient(amount);

	}

	return false;

}

bool Inventory::TryRemoveItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end())
		// Item does not exist
		return false;

	if (!((it_storage->second)->IsSufficient(amount) && (it_storage->second)->TryRemoveFromStack(amount)))
		// Not enough item, cannot remove
		return false;

	if ((it_storage->second)->ItemRanOut()) {
		// The item is used up (count reaches zero)
		// Remove item from hotbar
		HotBar::Instance()->RemoveItem(it_storage->first);

		// The item is only in the internal storage
		InventoryUI::Instance()->RemoveItemFromInventory(itemIndex);

		GameObject::Destroy(it_storage->second);
		storage.erase(it_storage);

	}

	return true;

}

bool Inventory::TryUseCurrent() {

	Item* currentItem = GetItem(HotBar::Instance()->GetSelectedItemIndex());
	if (!currentItem)
		return false;

	bool isUsed = currentItem->TryUse();

	if (isUsed)
		TryRemoveItem(currentItem->GetIndex());

	return isUsed;

}

int Inventory::GetItemCount(ItemIndex itemIndex) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->GetCurrentStack();

	}

	return 0;

}

Item* Inventory::GetItem(ItemIndex itemIndex) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return it->second;

	}

	return nullptr;

}

Inventory* Inventory::Instance() { return instance; }