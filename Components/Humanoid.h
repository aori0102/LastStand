/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>

#include <GameComponent.h>

class GameObject;

class Humanoid : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float health;
	float maxHealth;
	float stamina;
	float maxStamina;

public:

	std::function<void()> OnDeath;
	std::function<void()> OnDamaged;
	std::function<void()> OnHealed;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Humanoid(GameObject* initOwner);
	~Humanoid();
	void SetHealth(float amount);
	void SetMaxHealth(float amount);
	void Damage(float amount);
	void Heal(float amount);
	void DrainStamina(float amount);
	void GainStamina(float amount);
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;

};