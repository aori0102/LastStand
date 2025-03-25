#include <Consumable.h>

#include <GameComponent.h>
#include <Player.h>

Consumable::Consumable(ItemIndex initItemIndex) : Item(initItemIndex) {

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

void Consumable::Equip() {}

void Consumable::Dequip() {}

float Consumable::GetHealth() const { return health; }

float Consumable::GetStamina() const { return stamina; }