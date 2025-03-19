/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

class Player;

enum class ItemIndex {

	None,

	Pistol,
	Shotgun,

};

class Item {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	ItemIndex itemIndex;

protected:

	float useCooldown;
	bool stackable;
	bool usable;
	std::function<void()> OnEquip;
	std::function<void()> OnDequip;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Item(ItemIndex initItemIndex);

	virtual bool TryUse(Player* player) = 0;
	void Equip();
	void Dequip();
	bool IsUsable() const;
	bool IsStackable() const;
	ItemIndex GetIndex() const;

};