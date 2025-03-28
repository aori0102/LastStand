/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <Item.h>

class Player;

class Consumable : public Item {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float health;
	float stamina;

	friend class ItemManager;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Consumable(ItemIndex initItemIndex, int amount = 1);
	bool TryUse(Player* player) override; 
	bool TryAddToStack(int amount) override;
	bool TryRemoveFromStack(int amount) override;
	void Equip() override;
	void Dequip() override;
	int GetCurrentStack() const;
	float GetHealth() const;
	float GetStamina() const;

};