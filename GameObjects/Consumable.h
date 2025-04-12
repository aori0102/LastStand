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

	Consumable();
	void Equip() override;
	void Dequip() override;
	bool TryUse() override; 
	bool TryAddToStack(int amount) override;
	bool TryRemoveFromStack(int amount) override;
	int GetCurrentStack() const;
	float GetHealth() const;
	float GetStamina() const;

};