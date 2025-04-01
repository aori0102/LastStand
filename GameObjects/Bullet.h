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
	static const float BULLET_EXIST_TIME;
	static const float DAMAGE_INDICATOR_SHOW_TIME;
	static const float DAMAGE_INDICATOR_POP_UP_VELOCITY;
	static const float DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION;
	static const float DAMAGE_INDICATOR_ANGLE_OFFSET;
	static const int DAMAGE_INDICATOR_FONT_SIZE;
	static const int DAMAGE_INDICATOR_DECIMAL;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool hitHumanoid;		// Whether the bullet has hit something
	float damage;
	float spawnTime;	
	float hitTime;
	std::function<float(float)> indicatorOpacityFunction;
	std::function<Vector2(float)> indicatorOffsetFunction;
	Vector2 direction;
	Vector2 damageIndicatorPopUpDirection;
	GameObject* damageIndicator;	// On screen UI to show bullet's damage

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Bullet(Vector2 initPosition, Vector2 initDirection, float initDamage, bool isCrit);
	void Update() override;
	void OnCollisionEnter(BoxCollider* collider) override;
	void OnDestroy() override;

};