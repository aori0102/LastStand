#pragma once

#include <GameComponent.h>

using namespace std;

class ReloadUI;
class Player : public GameObject {

private:

	float playerForwardAngle;

	Vector2 forward;		// The vector towards the position the player is facing

	float movementSpeed;

	void Render();
	void HandleActions();

	ReloadUI* reloadUI;

public:

	Player();

	void Update() override;
	Vector2 GetForward() const;

};