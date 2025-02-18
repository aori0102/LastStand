#include <GameComponent.h>
#include <Item.h>

Inventory::Inventory(GameObject* initOwner) : GameComponent(initOwner) {

	holdingItem = nullptr;

}

void Inventory::AddItem(Item* newItem) {

	holdingItem = newItem;

}

void Inventory::UseCurrent(Player* player) {

	if (holdingItem)
		holdingItem->Use(player);

}

Item* Inventory::HoldingItem() {

	return holdingItem;

}