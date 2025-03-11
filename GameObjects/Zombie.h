/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameComponent.h>
#include <RenderManager.h>

enum class ZombieIndex {

	Normal,
	Lurker,
	Bomber,
	Tanker,

};

class ZombieAttribute {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

public:

	static const float HEALTH_MULTIPLIER;
	static const float DAMAGE_MULTIPLIER;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	float movementSpeed;
	float health;
	float damage;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	ZombieAttribute(float initMovementSpeed, float initHealth, float initDamage)
		: movementSpeed(initMovementSpeed), health(initHealth), damage(initDamage) {}

	ZombieAttribute()
		: movementSpeed(0.0f), health(0.0f), damage(0.0f) {}

};

class Zombie : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float HEALTH_BAR_VERTICAL_OFFSET;
	static const float KNOCKBACK_FORCE;
	static const float HEALTH_BAR_SCALE;
	static const std::string SPRITE_PATH;
	static const std::unordered_map<ZombieIndex, ZombieAttribute> ZOMBIE_BASE_ATTRIBUTE_MAP;
	static const std::unordered_map<ZombieIndex, SDL_Rect> ZOMBIE_SPRITE_CLIP_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	GameObject* healthBar;
	GameObject* target;

	ZombieIndex zombieIndex;
	ZombieAttribute* zombieAttribute;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Zombie(GameObject* initTarget, ZombieIndex initZombieIndex);

	void Update() override;
	void OnDestroy() override;
	void OnCollisionEnter(BoxCollider* other) override;

};