/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameObject.h>

class DamageIndicator : public GameObject {

private:

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

	static const int DAMAGE_INDICATOR_DECIMAL;
	static const int DAMAGE_INDICATOR_FONT_SIZE;
	static const float DAMAGE_INDICATOR_SHOW_TIME;
	static const float DAMAGE_INDICATOR_POP_UP_VELOCITY;
	static const float DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float initiateTime;
	Vector2 direction;
	Vector2 position;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void InitializeComponents();
	void RenderUI();
	float GetOpacity(float time);
	Vector2 GetOffset(float time);

public:

	DamageIndicator();
	void SetDamage(float damage, bool isCrit);
	void Initiate(Vector2 position, Vector2 direction);
	void Update() override;

};