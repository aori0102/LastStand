#pragma once

#include <unordered_map>

#include <Item.h>

class Player;
enum class ItemIndex;

enum class AmmunitionID {

	Slug,
	Nine_Mil,
	
};

class Ammunition : public Item {

private:

	AmmunitionID ammunitionID;

public:

	static const std::unordered_map<AmmunitionID, ItemIndex> AMMO_ITEM_INDEX_MAP;

	Ammunition(AmmunitionID initAmmunitionID, int amount = 1);

	AmmunitionID GetAmmunitionID() const;

	void Equip() override;
	void Dequip() override;
	bool TryAddToStack(int amount = 1) override;
	bool TryRemoveFromStack(int amount = 1) override;
	bool TryUse(Player* player) override;

};