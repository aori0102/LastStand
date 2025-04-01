/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Item.h>

#include <MediaManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

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