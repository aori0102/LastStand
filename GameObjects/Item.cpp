/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Item.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Item::Item(ItemIndex initItemIndex) {

	itemIndex = initItemIndex;

	useCooldown = 0.0f;
	stackable = false;
	usable = true;
	
	OnEquip = []() {};
	OnDequip = []() {};

}

void Item::Equip() { OnEquip(); }

void Item::Dequip() { OnDequip(); }

bool Item::IsUsable() const { return usable; }

bool Item::IsStackable() const { return stackable; }

ItemIndex Item::GetIndex() const { return itemIndex; }