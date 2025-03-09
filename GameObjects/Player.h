#pragma once

#include <GameComponent.h>
#include <unordered_map>
#include <RenderManager.h>

class Firearm;
class AnimationClip;

class Player : public GameObject {

private:

	enum class AnimationIndex {

		Idle,
		Shoot,

	};

	float playerForwardAngle;

	Vector2 forward;		// The vector towards the position the player is facing

	float movementSpeed;

	void HandleActions();
	void HandleMovement(Transform* transform);
	void HandleFacing(Transform* transform);

	bool canInteract;
	bool usingItem;

	Firearm* firearm;

	std::unordered_map<AnimationIndex, AnimationClip*> animationMap;
	AnimationIndex currentAnimationState;
	float currentAnimationTime;
	float currentAnimationStartTick;

	void InitializeAnimation();
	void InitializeData();

	void PlayerRender();

public:
	
	Player();

	void Update() override;
	Vector2 Forward() const;

	void DisableInteraction();
	void EnableInteraction();

	Firearm* GetFirearm();

};