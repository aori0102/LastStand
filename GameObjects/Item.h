/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

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

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Item(ItemIndex initItemIndex);

	virtual bool TryUse(Player* player) = 0;

	bool IsUsable() const;
	bool IsStackable() const;
	ItemIndex GetIndex();

};