#include <GameComponent.h>
#include <GameCore.h>
#include <PhysicsManager.h>

RigidBody::RigidBody(GameObject* initOwner) : GameComponent(initOwner) {

	drag = 1.0f;
	mass = 1.0f;

	initialForce = Vector2::zero;

	lastUpdateTick = 0.0f;

	PhysicsManager::RegisterRigidBody(this);

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

	PhysicsManager::UnregisterRigidBody(this);

}

Vector2 RigidBody::GetAcceleration() {

	return initialForce / mass;

}