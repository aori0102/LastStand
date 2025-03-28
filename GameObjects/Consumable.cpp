#include <Consumable.h>

#include <GameComponent.h>
#include <Player.h>

Consumable::Consumable(ItemIndex initItemIndex, int amount) : Item(initItemIndex, amount) {

	health = 0.0f;
	stamina = 0.0f;

}

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

void Consumable::Equip() {}

void Consumable::Dequip() {}

int Consumable::GetCurrentStack() const { return currentStack; }

float Consumable::GetHealth() const { return health; }

float Consumable::GetStamina() const { return stamina; }