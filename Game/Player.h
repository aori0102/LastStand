#pragma once

#include <GameComponent.h>

class Firearm;

class Player : public GameObject {

private:

	float playerForwardAngle;

	Vector2 forward;		// The vector towards the position the player is facing

	float movementSpeed;

	void Render();
	void HandleActions();
	void HandleMovement(Transform* transform);
	void HandleFacing(Transform* transform);

	bool canInteract;

	Firearm* firearm;

public:
	
	Player();

	void Update() override;
	Vector2 Forward() const;

	void DisableInteraction();
	void EnableInteraction();

	Firearm* GetFirearm();

};