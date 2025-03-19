/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Type.h>

class Bullet : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float KNOCKBACK_FORCE;
	static const float BULLET_VELOCITY;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float damage;
	float spawnTime;		// Control when the object would be destroyed
	Vector2 direction;
	GameObject* shooter;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Bullet(GameObject* initShooter, Vector2 initPosition, Vector2 initDirection, float initDamage);

	void Update() override;
	void OnCollisionEnter(BoxCollider* collider) override;

};