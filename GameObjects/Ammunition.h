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

enum class AmmunitionID {

	Slug,
	Nine_Mil,
	Five_Five_Six,
	
};

class Ammunition : public Item {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

public:

	static const std::unordered_map<AmmunitionID, ItemIndex> AMMO_ITEM_INDEX_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	AmmunitionID ammunitionID;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Ammunition(AmmunitionID initAmmunitionID, int amount = 1);
	void Equip() override;
	void Dequip() override;
	bool TryAddToStack(int amount = 1) override;
	bool TryRemoveFromStack(int amount = 1) override;
	bool TryUse(Player* player) override;
	AmmunitionID GetAmmunitionID() const;

};