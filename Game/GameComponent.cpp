#include <GameComponent.h>
#include <Game.h>
#include <Physics.h>

GameComponent::GameComponent(GameObject* initOwner) {

	if (!initOwner)
		throw new std::exception("Initialize game component with NULL game object");

	owner = initOwner;

	transform = owner->transform;

}

void GameComponent::OnComponentDestroyed() {}

GameObject* GameComponent::Owner() {

	return owner;

}