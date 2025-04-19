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
	static const float MONEY_MULTIPLIER;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	float movementSpeed;
	float health;
	float damage;
	float scale;
	float mass;
	int exp;
	int money;

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
	static const float HURT_VISUAL_DISPLAY_TIME;
	static const std::string SPRITE_PATH;
	static const std::unordered_map<ZombieIndex, ZombieAttribute> ZOMBIE_BASE_ATTRIBUTE_MAP;
	static const std::unordered_map<ZombieIndex, SDL_Rect> ZOMBIE_SPRITE_CLIP_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float lastGroanTick;
	float groanDelay;
	float lastHurtTick;
	bool displayHurt;
	ZombieIndex zombieIndex;
	Vector2 wanderTarget;
	GameObject* healthBar;
	ZombieAttribute* zombieAttribute;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeData();
	void InitializeComponents();
	void FollowPlayer();

public:

	Zombie();
	~Zombie();
	void Update() override;
	void OnCollisionEnter(BoxCollider* other) override;
	int GetExp() const;
	int GetMoney() const;

};