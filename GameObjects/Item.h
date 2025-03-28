﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

class Player;

enum class ItemIndex;
class Item {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	ItemIndex itemIndex;

protected:

	int currentStack;
	float useCooldown;
	bool stackable;
	bool usable;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Item(ItemIndex initItemIndex, int amount = 1);

	virtual void Equip() = 0;
	virtual void Dequip() = 0;
	virtual bool TryUse(Player* player) = 0;
	virtual bool TryAddToStack(int amount = 1);
	virtual bool TryRemoveFromStack(int amount = 1);
	bool IsSufficient(int amount) const;
	int GetCurrentStack() const;
	bool IsUsable() const;
	bool IsStackable() const;
	template <class T>
	bool IsType();
	template <class T>
	T* ToType();
	ItemIndex GetIndex() const;

};

#include <Item.inl>