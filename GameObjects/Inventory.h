/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

class Item;
enum class ItemIndex;

enum class HotBarSlotIndex {

	None,

	First,
	Second,
	Third,
	Forth,
	Fifth,

};

class Inventory {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct ItemState {
		Item* item;
		HotBarSlotIndex slot;
	};

	static const std::unordered_map<ItemIndex, int> STARTER_KIT;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<ItemIndex, ItemState*> storage;
	std::unordered_map<HotBarSlotIndex, ItemIndex> hotBar;
	HotBarSlotIndex currentSlotIndex;

	static Inventory* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

public:

	Inventory();
	~Inventory();
	void AddItem(ItemIndex itemIndex, int amount = 1);
	void SelectSlot(HotBarSlotIndex slotIndex);
	void ToggleInventory();
	void LinkItemToHotBar(HotBarSlotIndex hotBarSlotIndex, ItemIndex itemIndex);
	void SaveInventory();
	void LoadInventory();
	bool IsSufficient(ItemIndex itemIndex, int amount);
	bool TryRemoveItem(ItemIndex itemIndex, int amount = 1);
	bool TryUseCurrent();
	int GetItemCount(ItemIndex itemIndex);
	ItemIndex GetCurrentItemIndex();
	Item* GetCurrentItem();

	template <class T> std::vector<T*> GetItemListOfType();

	static Inventory* Instance();

};
#include <Inventory.inl>