/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <Item.h>

class Player;
enum class ItemIndex;

class Ammunition : public Item {

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	void SetAmmunitionItemIndex(ItemIndex initItemIndex);
	void Equip() override;
	void Dequip() override;
	void SetIndex(ItemIndex initItemIndex) override;
	bool TryAddToStack(int amount = 1) override;
	bool TryRemoveFromStack(int amount = 1) override;
	bool TryUse() override;

};