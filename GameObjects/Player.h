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
class HotBarUI;
class InventoryUI;
enum class ItemIndex;

enum class PlayerAttribute {
	ReloadSpeed,
	Accuracy,
	MaxHealth,

	None,
};

class Player : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	// The aiming error angle in degree
	const float MOVING_AIM_DEVIATION = 27.0f;
	const float STANDING_AIM_DEVIATION = 10.0f;
	const float ADS_AIM_DEVIATION = 5.0f;
	const float MOVEMENT_SPEED_CHANGE_RATE = 50.0f;
	const float CAMERA_AIM_ZOOM = 1.3f;
	const float DEFAULT_MOVEMENT_SPEED = 500.0f;
	const float AIM_MOVEMENT_SPEED = 300.0f;
	const float SPRINT_MOVEMENT_SPEED = 750.0f;
	const float STAMINA_DRAIN_RATE = 29.0f;
	const float STAMINA_RECOVERY_RATE = 4.0f;
	const float WALK_SOUND_DELAY = 0.6f;
	const float AIM_SOUND_DELAY = 0.9f;
	const float SPRINT_SOUND_DELAY = 0.35f;
	const float HURT_VISUAL_DISPLAY_TIME = 0.14f;

public:

	static const std::unordered_map<PlayerAttribute, float> DEFAULT_PLAYER_ATTRIBUTE_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool isMoving;
	bool isAiming;
	bool isSprinting;
	bool isHurtDisplay;
	float playerForwardAngle;
	float currentMovementSpeed;
	float targetMovementSpeed;
	float aimDeviation;
	float lastWalkSoundTick;
	float lastHurtTick;
	std::unordered_map<PlayerAttribute, float> playerAttributeMap;
	ItemIndex itemIndex;
	Vector2 forward;
	InventoryUI* inventoryUI;

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
	void HandleVisual();
	void InitializeAnimation();
	void InitializeData();
	void InitializeComponents();

public:

	Player();
	~Player();
	void PlayerRender();
	void GiveItem(ItemIndex itemIndex, int amount = 1);
	void SetAttribute(PlayerAttribute playerAttribute, float value);
	void LoadData();
	void SaveData();
	void Reset();
	void Update() override;
	int GetAmmoCount(ItemIndex ammoItemIndex);
	float GetAttribute(PlayerAttribute playerAttribute);
	bool TryConsumeAmmo(ItemIndex ammoItemIndex, int amount = 1);
	Vector2 GetAimingDirection();
	std::vector<Firearm*> GetFirearmList();

	static Player* Instance();

};