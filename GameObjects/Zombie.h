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
	static const float EXP_MULTIPLIER;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	float movementSpeed;
	float health;
	float damage;
	float exp;

};

class Zombie : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const float HEALTH_BAR_VERTICAL_OFFSET;
	static const float KNOCKBACK_FORCE;
	static const float HEALTH_BAR_SCALE;
	static const float GROAN_SOUND_DELAY_MIN;
	static const float GROAN_SOUND_DELAY_MAX;
	static const std::string SPRITE_PATH;
	static const std::unordered_map<ZombieIndex, ZombieAttribute> ZOMBIE_BASE_ATTRIBUTE_MAP;
	static const std::unordered_map<ZombieIndex, SDL_Rect> ZOMBIE_SPRITE_CLIP_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float lastGroanTick;
	float groanDelay;
	ZombieIndex zombieIndex;
	GameObject* healthBar;
	ZombieAttribute* zombieAttribute;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Zombie();
	~Zombie();
	void SetIndex(ZombieIndex initZombieIndex);
	void Update() override;
	void OnCollisionEnter(BoxCollider* other) override;
	float GetExp() const;

};