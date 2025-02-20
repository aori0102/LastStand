#include <GameComponent.h>

Humanoid::Humanoid(GameObject* initOwner) : GameComponent(initOwner) {

	health = 100.0f;
	maxHealth = 100.0f;

}

void Humanoid::Damage(float amount) {

	cout << "Damage " << amount << endl;

	health -= amount;

	if (health <= 0.0f)
		GameObject::Destroy(Owner());

}

void Humanoid::Heal(float amount) {

	health += amount;

	if (health > maxHealth)
		health = maxHealth;

}

float Humanoid::Health() const { return health; }