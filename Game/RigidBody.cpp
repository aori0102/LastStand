#include <GameComponent.h>
#include <Game.h>
#include <Physics.h>

RigidBody::RigidBody(GameObject* initOwner) : GameComponent(initOwner) {

	drag = 1.0f;
	mass = 1.0f;

	initialForce = Vector2::zero;

	lastUpdateTick = 0.0f;

	Physics::RegisterRigidBody(this);

}

void RigidBody::AddForce(Vector2 force) {

	initialForce += force;

	lastUpdateTick = Game::Time();

}

void RigidBody::Update() {

	if (initialForce == Vector2::zero)
		return;

	if (initialForce.Magnitude() > drag * (Game::Time() - lastUpdateTick))
		initialForce -= initialForce.Normalize() * drag * (Game::Time() - lastUpdateTick);
	else
		initialForce = Vector2::zero;

}

void RigidBody::OnComponentDestroyed() {

	Physics::UnregisterRigidBody(this);

}

Vector2 RigidBody::GetAcceleration() {

	return initialForce / mass;

}