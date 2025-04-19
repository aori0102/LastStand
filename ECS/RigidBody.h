/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Utils.h>

class GameObject;

class RigidBody : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float lastUpdateTick;
	Vector2 initialForce;

public:

	float drag;
	float mass;
	Vector2 momentum;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	RigidBody(GameObject* initOwner);
	void AddForce(Vector2 force);
	void Update();
	void OnComponentDestroyed() override;
	Vector2 GetAcceleration();

};