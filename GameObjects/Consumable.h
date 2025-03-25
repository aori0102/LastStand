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
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

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

	Consumable(ItemIndex initItemIndex);
	bool TryUse(Player* player) override; 
	void Equip() override;
	void Dequip() override;
	float GetHealth() const;
	float GetStamina() const;

};