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

Item::Item(ItemIndex initItemIndex) {

	itemIndex = initItemIndex;

	useCooldown = 0.0f;
	stackable = false;
	usable = true;
	
}

bool Item::IsUsable() const { return usable; }

bool Item::IsStackable() const { return stackable; }

ItemIndex Item::GetIndex() const { return itemIndex; }