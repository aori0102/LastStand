/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

class Item;
enum class ItemIndex;

class ItemManager {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static ItemManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	ItemManager();
	
	static ItemManager* Instance();

	Item* CreateItem(ItemIndex itemIndex, int amount = 1);

};