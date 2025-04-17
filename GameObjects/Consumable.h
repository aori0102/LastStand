/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <Item.h>

class Player;

struct ConsumableInfo {

	float health;
	float stamina;

};

class Consumable : public Item {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const std::unordered_map<ItemIndex, ConsumableInfo> CONSUMABLE_INFO_MAP;

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
	void SetIndex(ItemIndex initItemIndex) override;
	bool TryUse() override; 
	bool TryAddToStack(int amount) override;
	bool TryRemoveFromStack(int amount) override;
	int GetCurrentStack() const;
	float GetHealth() const;
	float GetStamina() const;

};