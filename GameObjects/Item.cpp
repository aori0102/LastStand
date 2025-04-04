/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Item.h>

#include <ItemManager.h>
#include <MediaManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Item::SetIndex(ItemIndex initItemIndex) {

	itemIndex = initItemIndex;

}

Item::Item() {

	itemIndex = ItemIndex::None;

	currentStack = 1;
	useCooldown = 0.0f;
	stackable = false;
	usable = true;

}

Item::Item(ItemIndex initItemIndex, int amount) {

	itemIndex = initItemIndex;

	currentStack = amount;
	useCooldown = 0.0f;
	stackable = false;
	usable = true;
	
}

int Item::GetCurrentStack() const { return currentStack; }

bool Item::IsSufficient(int amount) const { return amount <= currentStack; }

bool Item::IsUsable() const { return usable; }

bool Item::IsStackable() const { return stackable; }

ItemIndex Item::GetIndex() const { return itemIndex; }