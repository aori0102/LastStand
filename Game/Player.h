#pragma once

#include <GameComponent.h>
#include <unordered_map>

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

	void Render();
	void HandleActions();
	void HandleMovement(Transform* transform);
	void HandleFacing(Transform* transform);

	bool canInteract;

	Firearm* firearm;

	unordered_map<AnimationIndex, AnimationClip*> animationMap;
	AnimationIndex currentAnimationState;
	float currentAnimationTime;
	float currentAnimationStartTick;

	void InitializeAnimation();

public:
	
	Player();

	void Update() override;
	Vector2 Forward() const;

	void DisableInteraction();
	void EnableInteraction();

	Firearm* GetFirearm();

};