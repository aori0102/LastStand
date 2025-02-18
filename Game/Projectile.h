#pragma once

#include <Type.h>
#include <GameComponent.h>

using namespace std;

class Projectile : public GameObject {

private:

	Vector2 direction;
	float velocity;
	float damage;

	float spawnTime;		// Control when the object would be destroyed

	void Render();

public:

	Projectile(Vector2 initPosition, Vector2 initScale, Vector2 initDirection, float initVelocity, float initDamage);

	void Update() override;
	void OnCollisionEnter(BoxCollider* collider) override;

};