/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameComponent.h>
#include <RenderManager.h>

class Firearm;
class AnimationClip;

class Player : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	enum class AnimationIndex {

		Idle,
		Shoot,

	};

	// The aiming error angle in degree
	static const float MAX_AIMING_DEVIATION;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float playerForwardAngle;
	float movementSpeed;

	bool isMoving;

	Vector2 forward;

public:

	float currentAnimationTime;
	float currentAnimationStartTick;

	bool canInteract;
	bool usingItem;

	std::unordered_map<AnimationIndex, AnimationClip*> animationMap;

	Firearm* firearm;
	AnimationIndex currentAnimationState;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleActions();
	void HandleMovement();
	void HandleFacing();

public:

	Player();

	void InitializeAnimation();
	void InitializeData();
	void PlayerRender();
	void DisableInteraction();
	void EnableInteraction();
	void Update() override;

	Vector2 GetForward() const;
	Vector2 GetAimingDirection();

	Firearm* GetFirearm() const;

};