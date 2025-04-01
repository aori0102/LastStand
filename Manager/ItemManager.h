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

enum class ItemIndex {

	None,

	Pistol_M1911,
	Shotgun_Beretta1301,

	MedKit,

	Ammo_Slug,
	Ammo_9mm,

};

class ItemManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct ItemInfo {

		int price = 0;
		int shopStack = 1;
		std::string name = "N/A";
		SDL_Rect iconClip = { 0, 0, 0, 0 };

	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<ItemIndex, ItemInfo> itemInfoMap;

	static ItemManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeItemInfo();

public:

	ItemManager();
	~ItemManager();
	void LinkItemIcon(ItemIndex itemIndex, Image* out);
	int GetItemPrice(ItemIndex itemIndex);
	int GetItemShopStack(ItemIndex itemIndex);
	std::string GetItemName(ItemIndex itemIndex);
	Item* CreateItem(ItemIndex itemIndex, int amount = 1);

	static ItemManager* Instance();

};