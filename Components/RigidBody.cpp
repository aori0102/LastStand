/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <RigidBody.h>

#include <GameCore.h>
#include <PhysicsManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

RigidBody::RigidBody(GameObject* initOwner) : GameComponent(initOwner) {

	lastUpdateTick = 0.0f;
	initialForce = Vector2::zero;

	drag = 1.0f;
	mass = 1.0f;
	momentum = Vector2::zero;

	PhysicsManager::Instance()->RegisterRigidBody(this);

}

void RigidBody::AddForce(Vector2 force) {

	initialForce += force;

	lastUpdateTick = GameCore::Time();

}

void RigidBody::Update() {

	if (initialForce == Vector2::zero)
		return;

	if (initialForce.Magnitude() > drag * (GameCore::Time() - lastUpdateTick))
		initialForce -= initialForce.Normalize() * drag * (GameCore::Time() - lastUpdateTick);
	else
		initialForce = Vector2::zero;

}

void RigidBody::OnComponentDestroyed() {

	PhysicsManager::Instance()->UnregisterRigidBody(this);

}

Vector2 RigidBody::GetAcceleration() {

	return initialForce / mass;

}