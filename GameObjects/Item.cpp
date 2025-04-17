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

Item::Item() {

	itemIndex = ItemIndex::None;

	currentStack = 1;
	useCooldown = 0.0f;
	stackable = false;
	usable = true;

}

void Item::SetAmount(int amount) {

	currentStack = amount;

}

int Item::GetCurrentStack() const { return currentStack; }

bool Item::IsSufficient(int amount) const { return amount <= currentStack; }

bool Item::IsUsable() const { return usable; }

bool Item::IsStackable() const { return stackable; }

ItemIndex Item::GetIndex() const { return itemIndex; }

bool Item::ItemRanOut() { return currentStack == 0; }