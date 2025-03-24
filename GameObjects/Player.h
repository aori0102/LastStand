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
	static const float MOVING_AIM_DEVIATION;
	static const float STANDING_AIM_DEVIATION;
	static const float ADS_AIM_DEVIATION;
	static const float MOVEMENT_SPEED_CHANGE_RATE;
	static const float CAMERA_AIM_ZOOM;
	static const float DEFAULT_MOVEMENT_SPEED;
	static const float AIM_MOVEMENT_SPEED;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float playerForwardAngle;
	float currentMovementSpeed;
	float targetMovementSpeed;
	float aimDeviation;
	bool isMoving;
	bool isAiming;
	Vector2 forward;
	ItemIndex itemIndex;
	static Player* instance;

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
	Vector2 GetAimingDirection();

	std::vector<Firearm*> GetFirearmList();

	static Player* Instance();

};