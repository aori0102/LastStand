#pragma once

#include <GameComponent.h>
#include <RenderManager.h>
#include <unordered_map>

enum class ZombieIndex {

	Normal,
	Lurker,
	Bomber,
	Tanker,

};

class ZombieAttribute {

public:

	static const float HEALTH_MULTIPLIER;
	static const float DAMAGE_MULTIPLIER;

	float movementSpeed;
	float health;
	float damage;

	ZombieAttribute(float initMovementSpeed, float initHealth, float initDamage)
		: movementSpeed(initMovementSpeed), health(initHealth), damage(initDamage) {}

	ZombieAttribute()
		: movementSpeed(0.0f), health(0.0f), damage(0.0f) {}

};

class Zombie : public GameObject {

private:

	static const std::unordered_map<ZombieIndex, ZombieAttribute> ZOMBIE_BASE_ATTRIBUTE_MAP;

private:

	static const std::string SPRITE_PATH;
	static const std::string HEALTH_BAR_PATH;
	static const Vector2 HEALTH_BAR_SCALE;
	static const float HEALTH_BAR_VERTICAL_OFFSET;
	static const float KNOCKBACK_FORCE;

	GameObject* healthBar;
	GameObject* target;

	ZombieIndex zombieIndex;
	ZombieAttribute* zombieAttribute;

public:

	Zombie(GameObject* initTarget, ZombieIndex initZombieIndex);

	void Update() override;
	void OnDestroy() override;
	void OnCollisionEnter(BoxCollider* other) override;

};