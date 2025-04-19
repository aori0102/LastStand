/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <GameCore.h>
#include <PhysicsManager.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

GameComponent::GameComponent(GameObject* initOwner) {

	if (!initOwner)
		throw std::exception("Initialize game component with NULL GameObject owner");

	owner = initOwner;

	transform = owner->transform;

}

void GameComponent::OnComponentDestroyed() {}

void GameComponent::OnComponentUpdate() {}

GameObject* GameComponent::Owner() {

	return owner;

}