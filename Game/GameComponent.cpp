#include <GameComponent.h>
#include <Game.h>
#include <Physics.h>

GameComponent::GameComponent(GameObject* initOwner) {

	if (!initOwner)
		throw new exception("Initialize game component with NULL game object");

	owner = initOwner;

}

void GameComponent::OnComponentDestroyed() {}