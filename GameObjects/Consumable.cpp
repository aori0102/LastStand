/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Consumable.h>

#include <GameComponent.h>
#include <Humanoid.h>
#include <ItemManager.h>
#include <Player.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const std::unordered_map<ItemIndex, ConsumableInfo> Consumable::CONSUMABLE_INFO_MAP = {
	{ ItemIndex::MedKit, ConsumableInfo{
		.health = 36.0f,
		.stamina = 7.0f,
	}
	},
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Consumable::Consumable() {

	health = 0.0f;
	stamina = 0.0f;

}

void Consumable::Equip() {}

void Consumable::Dequip() {}

void Consumable::SetIndex(ItemIndex initItemIndex) {

	if (!ItemManager::Instance()->IsIndexOfType<Consumable>(initItemIndex))
		throw std::exception("Invalid index for type Consumable.");

	itemIndex = initItemIndex;

	ConsumableInfo info = CONSUMABLE_INFO_MAP.at(itemIndex);
	health = info.health;
	stamina = info.stamina;

}

bool Consumable::TryUse() {

	Humanoid* humanoid = Player::Instance()->GetComponent<Humanoid>();

	if (!humanoid)
		return false;

	humanoid->Heal(health);
	humanoid->GainStamina(stamina);

	return true;

}

bool Consumable::TryAddToStack(int amount) {

	currentStack += amount;

	return true;

}

bool Consumable::TryRemoveFromStack(int amount) {

	if (!IsSufficient(amount))
		return false;

	currentStack -= amount;

	return true;

}

int Consumable::GetCurrentStack() const { return currentStack; }

float Consumable::GetHealth() const { return health; }

float Consumable::GetStamina() const { return stamina; }