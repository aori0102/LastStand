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
#include <Item.h>
#include <ItemManager.h>
#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Inventory::Inventory(GameObject* initOwner) : GameComponent(initOwner) {

	if (!initOwner->IsA<Player>())
		throw std::exception("Inventory must belong to a player!");

	storage = {};
	hotBar = {
		{ InventorySlotIndex::None, ItemIndex::None },
		{ InventorySlotIndex::First, ItemIndex::None },
		{ InventorySlotIndex::Second, ItemIndex::None },
		{ InventorySlotIndex::Third, ItemIndex::None },
		{ InventorySlotIndex::Forth, ItemIndex::None },
		{ InventorySlotIndex::Fifth, ItemIndex::None },
	};

	currentSlotIndex = InventorySlotIndex::None;

	hotBarUI = new HotBarUI;

}

void Inventory::AddItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end() || !storage.at(itemIndex)) {

		// Item not found in inventory
		
		storage[itemIndex] = new ItemState{
			.item = ItemManager::Instance()->CreateItem(itemIndex, amount),
			.slot = InventorySlotIndex::None,
		};

		for (auto it_hotbar = hotBar.begin(); it_hotbar != hotBar.end(); it_hotbar++) {

			if (it_hotbar->first != InventorySlotIndex::None && it_hotbar->second == ItemIndex::None) {
				// A slot is available for the brand new item
				storage.at(itemIndex)->slot = it_hotbar->first;
				it_hotbar->second = itemIndex;
				hotBarUI->UpdateSlot(it_hotbar->first, itemIndex, amount);
				return;

			}

		}

	} else {

		// Item found in inventory
		if ((it_storage->second)->slot != InventorySlotIndex::None && (it_storage->second)->item->TryAddToStack(amount)) {

			// Item is present in hotbar
			hotBarUI->UpdateSlot((it_storage->second)->slot, itemIndex, (it_storage->second)->item->GetCurrentStack());

		}

	}

}

bool Inventory::TryRemoveItem(ItemIndex itemIndex, int amount) {

	auto it_storage = storage.find(itemIndex);
	if (it_storage == storage.end())
		// Item does not exist
		return false;

	if ((it_storage->second)->item->IsSufficient(amount) && (it_storage->second)->item->TryRemoveFromStack(amount)) {
		// There is enough item
		// Update item in hotbar if present
		if ((it_storage->second)->slot != InventorySlotIndex::None)
			hotBarUI->UpdateSlot((it_storage->second)->slot, itemIndex, (it_storage->second)->item->GetCurrentStack());

	} else
		return false;

	if ((it_storage->second)->item->GetCurrentStack() == 0) {

		// Remove item from hotbar if present
		if ((it_storage->second)->slot != InventorySlotIndex::None) {

			hotBarUI->UpdateSlot((it_storage->second)->slot, ItemIndex::None);

			hotBar.at((it_storage->second)->slot) = ItemIndex::None;

		}

		// Item reaches zero, delete
		delete it_storage->second;
		storage.erase(it_storage);

	}

	return true;

}

int Inventory::GetItemCount(ItemIndex itemIndex) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->item->GetCurrentStack();

	}

	return 0;

}

bool Inventory::IsSufficient(ItemIndex itemIndex, int amount) {

	for (auto it = storage.begin(); it != storage.end(); it++) {

		if (it->first == itemIndex)
			return (it->second)->item->IsSufficient(amount);

	}

	return false;

}

void Inventory::SelectSlot(InventorySlotIndex slotIndex) {

	Item* currentItem = GetCurrentItem();

	if (currentItem)
		currentItem->Dequip();

	if (currentSlotIndex == slotIndex)
		currentSlotIndex = InventorySlotIndex::None;
	else
		currentSlotIndex = slotIndex;

	currentItem = GetCurrentItem();

	if (currentItem)
		currentItem->Equip();

	hotBarUI->SwitchSlot(currentSlotIndex);

}

bool Inventory::TryUseCurrent() {

	if (currentSlotIndex == InventorySlotIndex::None)
		return false;

	Item* currentItem = GetCurrentItem();
	if (!currentItem)
		return false;

	bool isUsed = currentItem->TryUse(Owner()->As<Player>());

	if (isUsed)
		TryRemoveItem(currentItem->GetIndex());

	return isUsed;

}

ItemIndex Inventory::GetCurrentItemIndex() {

	if (currentSlotIndex == InventorySlotIndex::None)
		return ItemIndex::None;

	return hotBar.at(currentSlotIndex);

}

Item* Inventory::GetCurrentItem() {

	if (currentSlotIndex == InventorySlotIndex::None)
		return nullptr;

	auto it = storage.find(hotBar.find(currentSlotIndex)->second);

	if (it == storage.end())
		return nullptr;
	else
		return (it->second)->item;

}