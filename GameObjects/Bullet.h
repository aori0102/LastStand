﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Utils.h>

class Humanoid;

class Bullet : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float KNOCKBACK_FORCE;
	static const float BULLET_VELOCITY;
	static const float BULLET_EXIST_TIME;
	static const float DAMAGE_INDICATOR_ANGLE_OFFSET;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isCrit;
	float damage;
	float spawnTime;	
	Vector2 direction;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void OnHumanoidHit(Humanoid* target);
	void InitializeComponents();

public:

	Bullet();
	void Update() override;
	void SetUpBullet(Vector2 initPosition, Vector2 initDirection, float damage, bool initIsCrit);
	void OnCollisionEnter(BoxCollider* collider) override;

};