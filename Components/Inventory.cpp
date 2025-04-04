/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <exception>

#include <Consumable.h>
#include <Firearm.h>
#include <HotBarUI.h>
#include <InventoryUI.h>
#include <Item.h>
#include <ItemManager.h>
#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Inventory::OnComponentDestroyed() {

	GameObject::Destroy(hotBarUI);
	hotBarUI = nullptr;

	GameObject::Destroy(inventoryUI);
	inventoryUI = nullptr;
	
	for (auto it = storage.begin(); it != storage.end(); it++) {

		std::cout << it->second << std::endl;
		std::cout << it->second->item << std::endl;

		ItemManager::Instance()->NukeItem((it->second)->item);

		delete (it->second);

	}

	storage.clear();

}

Inventory::Inventory(GameObject* initOwner) : GameComponent(initOwner) {

	if (!initOwner->IsA<Player>())
		throw std::exception("Inventory must belong to a player!");

	storage = {};
	hotBar = {
		{ HotBarSlotIndex::None, ItemIndex::None },
		{ HotBarSlotIndex::First, ItemIndex::None },
		{ HotBarSlotIndex::Second, ItemIndex::None },
		{ HotBarSlotIndex::Third, ItemIndex::None },
		{ HotBarSlotIndex::Forth, ItemIndex::None },
		{ HotBarSlotIndex::Fifth, ItemIndex::None },
	};
	currentSlotIndex = HotBarSlotIndex::None;
	hotBarUI = GameObject::Instantiate<HotBarUI>();
	inventoryUI = GameObject::Instantiate<InventoryUI>();
	inventoryUI->Disable();

}

void Inventory::AddItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end() || !storage.at(itemIndex)) {
		// Item not found in inventory

		storage[itemIndex] = new ItemState{
			.item = ItemManager::Instance()->CreateItem(itemIndex, amount),
			.slot = HotBarSlotIndex::None,
		};

		for (auto it_hotbar = hotBar.begin(); it_hotbar != hotBar.end(); it_hotbar++) {

			if (it_hotbar->first != HotBarSlotIndex::None && it_hotbar->second == ItemIndex::None) {
				// A slot is available for the brand new item
				storage.at(itemIndex)->slot = it_hotbar->first;
				it_hotbar->second = itemIndex;
				hotBarUI->UpdateSlot(it_hotbar->first, itemIndex, amount);
				inventoryUI->UpdateHotBarSlot(itemIndex, amount, it_hotbar->first);
				return;

			}

		}

		// No hotbar slot is available
		inventoryUI->UpdateInventorySlot(itemIndex, amount);

	} else {
		// Item found in inventory

		if ((it_storage->second)->slot != HotBarSlotIndex::None && (it_storage->second)->item->TryAddToStack(amount)) {
			// Item is present in hotbar

			hotBarUI->UpdateSlot((it_storage->second)->slot, itemIndex, (it_storage->second)->item->GetCurrentStack());
			inventoryUI->UpdateHotBarSlot(itemIndex, (it_storage->second)->item->GetCurrentStack(), (it_storage->second)->slot);

		} else {
			// Item is not present in hotbar. Just add to internal storage

			inventoryUI->UpdateInventorySlot(itemIndex, (it_storage->second)->item->GetCurrentStack());

		}

	}

}

void Inventory::SelectSlot(HotBarSlotIndex slotIndex) {

	Item* currentItem = GetCurrentItem();

	if (currentItem)
		currentItem->Dequip();

	if (currentSlotIndex == slotIndex)
		currentSlotIndex = HotBarSlotIndex::None;
	else
		currentSlotIndex = slotIndex;

	currentItem = GetCurrentItem();

	if (currentItem)
		currentItem->Equip();

	hotBarUI->SwitchSlot(currentSlotIndex);

}

void Inventory::ToggleInventory() {

	inventoryUI->IsActive() ? inventoryUI->Disable() : inventoryUI->Enable();

}

void Inventory::LinkItemToHotBar(HotBarSlotIndex hotBarSlotIndex, ItemIndex itemIndex) {

	if (hotBarSlotIndex == HotBarSlotIndex::None)
		return;

	auto it_hotBar = hotBar.find(hotBarSlotIndex);
	if (it_hotBar == hotBar.end() || it_hotBar->second == itemIndex)
		// The item is not found or already the same
		return;

	// If the item in the hot bar is a valid item and still belongs to the same hotbar (was not moved to a 
	// different one), make it no longer belongs to the hot bar. This prevents more than one item
	// info pointing to the same hot bar
	if (it_hotBar->second != ItemIndex::None && (storage.find(it_hotBar->second)->second)->slot == it_hotBar->first)
		storage.find(it_hotBar->second)->second->slot = HotBarSlotIndex::None;

	if (itemIndex == ItemIndex::None) {

		hotBarUI->UpdateSlot(hotBarSlotIndex, itemIndex, 0);
		it_hotBar->second = itemIndex;
		return;

	}

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end())
		// Item does not exist in inventory
		return;

	(it_storage->second)->slot = hotBarSlotIndex;
	it_hotBar->second = itemIndex;
	hotBarUI->UpdateSlot(hotBarSlotIndex, itemIndex, (it_storage->second)->item->GetCurrentStack());

}

bool Inventory::IsSufficient(ItemIndex itemIndex, int amount) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->item->IsSufficient(amount);

	}

	return false;

}

bool Inventory::TryRemoveItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end())
		// Item does not exist
		return false;

	if ((it_storage->second)->item->IsSufficient(amount) && (it_storage->second)->item->TryRemoveFromStack(amount)) {
		// There is enough item
		// Update item in hotbar if present
		if ((it_storage->second)->slot != HotBarSlotIndex::None)
			hotBarUI->UpdateSlot((it_storage->second)->slot, itemIndex, (it_storage->second)->item->GetCurrentStack());

	} else
		// Not enough item, cannot remove
		return false;

	if ((it_storage->second)->item->GetCurrentStack() == 0) {
		// The item is used up (count reaches zero)
		// Remove item from hotbar if present
		if ((it_storage->second)->slot != HotBarSlotIndex::None) {

			hotBarUI->UpdateSlot((it_storage->second)->slot, ItemIndex::None);
			hotBar.at((it_storage->second)->slot) = ItemIndex::None;

			inventoryUI->UpdateHotBarSlot(ItemIndex::None, 0, (it_storage->second)->slot);

		} else
			// The item is only in the internal storage
			inventoryUI->UpdateInventorySlot(itemIndex, 0);

		delete it_storage->second;
		storage.erase(it_storage);

	}

	return true;

}

bool Inventory::TryUseCurrent() {

	if (currentSlotIndex == HotBarSlotIndex::None)
		return false;

	Item* currentItem = GetCurrentItem();
	if (!currentItem)
		return false;

	bool isUsed = currentItem->TryUse(Owner()->As<Player>());

	if (isUsed)
		TryRemoveItem(currentItem->GetIndex());

	return isUsed;

}

int Inventory::GetItemCount(ItemIndex itemIndex) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->item->GetCurrentStack();

	}

	return 0;

}

ItemIndex Inventory::GetCurrentItemIndex() {

	if (currentSlotIndex == HotBarSlotIndex::None)
		return ItemIndex::None;

	return hotBar.at(currentSlotIndex);

}

Item* Inventory::GetCurrentItem() {

	if (currentSlotIndex == HotBarSlotIndex::None)
		return nullptr;

	auto it = storage.find(hotBar.find(currentSlotIndex)->second);

	if (it == storage.end())
		return nullptr;
	else
		return (it->second)->item;

}