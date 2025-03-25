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

	Pistol_M1911,
	Shotgun_Beretta1301,

	MedKit,

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

	virtual void Equip() = 0;
	virtual void Dequip() = 0;
	virtual bool TryUse(Player* player) = 0;
	bool IsUsable() const;
	bool IsStackable() const;
	template <class T>
	bool IsType();
	template <class T>
	T* ToType();
	ItemIndex GetIndex() const;

};

#include <Item.inl>