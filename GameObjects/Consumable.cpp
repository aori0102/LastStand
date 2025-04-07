/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Consumable.h>

#include <GameComponent.h>
#include <Humanoid.h>
#include <Player.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Consumable::Consumable(ItemIndex initItemIndex, int amount) : Item(initItemIndex, amount) {

	health = 0.0f;
	stamina = 0.0f;

}

void Consumable::Equip() {}

void Consumable::Dequip() {}

bool Consumable::TryUse(Player* player) {

	Humanoid* humanoid = player->GetComponent<Humanoid>();

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