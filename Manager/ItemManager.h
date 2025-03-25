/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

class Item;
enum class ItemIndex;

class ItemManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static ItemManager* instance;
	std::unordered_map<ItemIndex, Item*> prefabMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	ItemManager();
	
	static ItemManager* Instance();

	Item* CreateItem(ItemIndex itemIndex, int amount = 1);

};