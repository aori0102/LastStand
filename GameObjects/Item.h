/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
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

protected:

	friend class ItemManager;

	int currentStack;
	float useCooldown;
	bool stackable;
	bool usable;

	ItemIndex itemIndex;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void SetAmount(int amount);

	virtual void SetIndex(ItemIndex initItemIndex) = 0;

public:

	Item();
	int GetCurrentStack() const;
	bool IsSufficient(int amount) const;
	bool IsUsable() const;
	bool IsStackable() const;
	ItemIndex GetIndex() const;

	virtual void Equip() = 0;
	virtual void Dequip() = 0;
	virtual bool TryUse() = 0;
	virtual bool TryAddToStack(int amount = 1) = 0;
	virtual bool TryRemoveFromStack(int amount = 1) = 0;
	virtual bool ItemRanOut();
	
	template <class T> bool IsType();
	template <class T> T* ToType();

};
#include <Item.inl>