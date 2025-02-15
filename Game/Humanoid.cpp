#include <GameComponent.h>

Humanoid::Humanoid(GameObject* initOwner) : GameComponent(initOwner) {

	health = 100.0f;
	maxHealth = 100.0f;

}

void Humanoid::SetMaxHealth(float newMaxHealth) {

	maxHealth = newMaxHealth;

}

void Humanoid::Damage(float amount) {

	health -= amount;

	if (health <= 0.0f)
		GameObject::Destroy(GetOwner());

}

float Humanoid::GetHealth() {

	return health;

}

float Humanoid::GetMaxHealth() {

	return maxHealth;

}