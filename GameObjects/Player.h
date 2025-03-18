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
enum class ItemIndex;

class Player : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

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
	ItemIndex itemIndex;

public:

	float currentAnimationTime;
	float currentAnimationStartTick;

	bool canInteract;
	bool usingItem;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleActions();
	void HandleMovement();
	void HandleFacing();
	void InitializeAnimation();
	void InitializeData();

public:

	Player();

	void PlayerRender();
	void DisableInteraction();
	void EnableInteraction();
	void Update() override;

	Vector2 GetForward() const;
	Vector2 GetAimingDirection() const;

};