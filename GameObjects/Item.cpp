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

bool Item::TryAddToStack(int amount) { return false; }

bool Item::TryRemoveFromStack(int amount) { return false; }

bool Item::IsSufficient(int amount) const { return amount <= currentStack; }

int Item::GetCurrentStack() const { return currentStack; }

bool Item::IsUsable() const { return usable; }

bool Item::IsStackable() const { return stackable; }

ItemIndex Item::GetIndex() const { return itemIndex; }