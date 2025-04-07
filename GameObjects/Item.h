﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

#include <GameComponent.h>

class Player;
enum class ItemIndex;

class Item : public GameObject {

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

protected:

	void SetIndex(ItemIndex initItemIndex);

public:

	Item();
	Item(ItemIndex initItemIndex, int amount = 1);
	int GetCurrentStack() const;
	bool IsSufficient(int amount) const;
	bool IsUsable() const;
	bool IsStackable() const;
	ItemIndex GetIndex() const;

	virtual void Equip() = 0;
	virtual void Dequip() = 0;
	virtual bool TryUse(Player* player) = 0;
	virtual bool TryAddToStack(int amount = 1) = 0;
	virtual bool TryRemoveFromStack(int amount = 1) = 0;
	
	template <class T> bool IsType();
	template <class T> T* ToType();

};
#include <Item.inl>