/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <exception>

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
		{ InventorySlotIndex::None, nullptr },
		{ InventorySlotIndex::First, nullptr },
		{ InventorySlotIndex::Second, nullptr },
		{ InventorySlotIndex::Third, nullptr },
		{ InventorySlotIndex::Forth, nullptr },
		{ InventorySlotIndex::Fifth, nullptr },
	};

	currentSlotIndex = InventorySlotIndex::None;

}

void Inventory::AddItem(ItemIndex itemIndex) {

	if (storage.find(itemIndex) == storage.end() || !storage.at(itemIndex)) {

		storage[itemIndex] = ItemManager::Instance()->CreateItem(itemIndex);

		for (auto it = hotBar.begin(); it != hotBar.end(); it++) {

			if (it->first != InventorySlotIndex::None && !it->second) {

				it->second = storage.at(itemIndex);
				return;

			}
			
		}

	}

}

void Inventory::SelectSlot(InventorySlotIndex slotIndex) {

	if (currentSlotIndex != InventorySlotIndex::None && hotBar.at(currentSlotIndex))
		hotBar.at(currentSlotIndex)->Dequip();

	if (currentSlotIndex == slotIndex)
		currentSlotIndex = InventorySlotIndex::None;
	else
		currentSlotIndex = slotIndex;

	if (currentSlotIndex != InventorySlotIndex::None && hotBar.at(currentSlotIndex))
		hotBar.at(currentSlotIndex)->Equip();

}

bool Inventory::TryUseCurrent() {

	if (currentSlotIndex == InventorySlotIndex::None || !hotBar.at(currentSlotIndex))
		return false;

	return hotBar.at(currentSlotIndex)->TryUse(Owner()->As<Player>());

}

ItemIndex Inventory::GetCurrentItemIndex() {

	if (currentSlotIndex == InventorySlotIndex::None || !hotBar.at(currentSlotIndex))
		return ItemIndex::None;

	return hotBar.at(currentSlotIndex)->GetIndex();

}

Item* Inventory::GetCurrentItem() {

	if (currentSlotIndex == InventorySlotIndex::None)
		return nullptr;

	return hotBar.at(currentSlotIndex);

}