#pragma once

#include <GameComponent.h>

class ReloadUI;
class FirearmUI;

class Player : public GameObject {

private:

	float playerForwardAngle;

	Vector2 forward;		// The vector towards the position the player is facing

	float movementSpeed;

	void Render();
	void HandleActions();

	bool canInteract;

public:
	
	Player();

	void Update() override;
	Vector2 Forward() const;

	void DisableInteraction();
	void EnableInteraction();

};