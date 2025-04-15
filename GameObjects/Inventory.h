/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

class Item;
enum class ItemIndex;

class Inventory {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const std::unordered_map<ItemIndex, int> STARTER_KIT;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<ItemIndex, Item*> storage;

	static Inventory* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Inventory();
	~Inventory();
	void AddItem(ItemIndex itemIndex, int amount = 1);
	void ToggleInventory();
	void SaveInventory();
	void LoadInventory();
	void ResetInventory();
	bool IsSufficient(ItemIndex itemIndex, int amount);
	bool TryRemoveItem(ItemIndex itemIndex, int amount = 1);
	bool TryUseCurrent();
	bool IsItemPresent(ItemIndex itemIndex);
	int GetItemCount(ItemIndex itemIndex);
	Item* GetItem(ItemIndex itemIndex);

	template <class T> std::vector<T*> GetItemListOfType();

	static Inventory* Instance();

};
#include <Inventory.inl>