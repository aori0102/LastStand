﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Humanoid.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Humanoid::Humanoid(GameObject* initOwner) : GameComponent(initOwner) {

	health = 100.0f;
	maxHealth = 100.0f;
	stamina = 100.0f;
	maxStamina = 100.0f;

	OnDeath = []() {};
	OnDamaged = []() {};
	OnHealed = []() {};

}

Humanoid::~Humanoid() {

	OnDeath = []() {};
	OnDamaged = []() {};

}

void Humanoid::SetHealth(float amount) {

	health = amount;
	maxHealth = std::max(maxHealth, amount);

}

void Humanoid::SetMaxHealth(float amount) {

	maxHealth = amount;

}

void Humanoid::Damage(float amount) {

	if (health <= 0.0f)	// Already dead
		return;

	health -= amount;

	if (health <= 0.0f)
		OnDeath();
	else
		OnDamaged();

}

void Humanoid::Heal(float amount) {

	health += amount;
	OnHealed();

	if (health > maxHealth)
		health = maxHealth;

}

void Humanoid::DrainStamina(float amount) {

	stamina -= amount;

	if (stamina < 0.0f)
		stamina = 0.0f;

}

void Humanoid::GainStamina(float amount) {

	stamina += amount;

	if (stamina > maxStamina)
		stamina = maxStamina;

}

float Humanoid::GetHealth() const { return health; }

float Humanoid::GetMaxHealth() const { return maxHealth; }

float Humanoid::GetStamina() const { return stamina; }

float Humanoid::GetMaxStamina() const { return maxStamina; }