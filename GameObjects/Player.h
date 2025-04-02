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
enum class AmmunitionID;

enum class PlayerAttribute {
	ReloadSpeed,
	Accuracy,
	MaxHealth,
};

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
	static const float SPRINT_MOVEMENT_SPEED;
	static const float STAMINA_DRAIN_RATE;
	static const float STAMINA_RECOVERY_RATE;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isMoving;
	bool isAiming;
	bool isSprinting;
	float playerForwardAngle;
	float currentMovementSpeed;
	float targetMovementSpeed;
	float aimDeviation;
	std::unordered_map<PlayerAttribute, float> playerAttributeMap;
	ItemIndex itemIndex;
	Vector2 forward;

	static Player* instance;

public:

	bool usingItem;
	float currentAnimationTime;
	float currentAnimationStartTick;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleActions();
	void HandleMovement();
	void HandleFacing();
	void HandleStamina();
	void InitializeAnimation();
	void InitializeData();

public:

	Player();
	void PlayerRender();
	void GiveItem(ItemIndex itemIndex, int amount = 1);
	void SetAttribute(PlayerAttribute playerAttribute, float value);
	void Update() override;
	void OnDestroy() override;
	int GetAmmoCount(AmmunitionID);
	float GetAttribute(PlayerAttribute playerAttribute);
	bool TryConsumeAmmo(AmmunitionID ammunitionID, int amount = 1);
	Vector2 GetAimingDirection();
	std::vector<Firearm*> GetFirearmList();

	static Player* Instance();

};