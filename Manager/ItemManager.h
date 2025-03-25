/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <string>
#include <unordered_map>

#include <SDL.h>

class Item;
class Image;
enum class ItemIndex;

class ItemManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	struct ItemInfo {

		SDL_Rect iconClip = { 0, 0, 0, 0 };
		int price = 0;
		std::string name = "N/A";

	};

	static ItemManager* instance;
	std::unordered_map<ItemIndex, ItemInfo> itemInfoMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	ItemManager();
	
	static ItemManager* Instance();
	Item* CreateItem(ItemIndex itemIndex, int amount = 1);
	void LinkItemIcon(ItemIndex itemIndex, Image* out);
	int GetItemPrice(ItemIndex itemIndex);
	std::string GetItemName(ItemIndex itemIndex);

};