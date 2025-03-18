#include <GameComponent.h>
#include <GameCore.h>
#include <PhysicsManager.h>

GameComponent::GameComponent(GameObject* initOwner) {

	if (!initOwner)
		throw std::exception("Initialize game component with NULL game object");

	owner = initOwner;

	transform = owner->transform;

}

void GameComponent::OnComponentDestroyed() {}

void GameComponent::OnComponentUpdate() {}

GameObject* GameComponent::Owner() {

	return owner;

}