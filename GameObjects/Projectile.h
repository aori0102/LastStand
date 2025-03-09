#pragma once

#include <Type.h>
#include <GameComponent.h>

class Projectile : public GameObject {

private:

	Vector2 direction;
	float velocity;
	float damage;

	float spawnTime;		// Control when the object would be destroyed

	GameObject* shooter;

	static const float KNOCKBACK_FORCE;

public:

	Projectile(GameObject* initShooter, Vector2 initPosition, Vector2 initDirection, float initVelocity, float initDamage);

	void Update() override;
	void OnCollisionEnter(BoxCollider* collider) override;

};