/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <set>

#include <GameComponent.h>
#include <Utils.h>

enum class Layer;

class BoxCollider : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool enabled;

public:

	std::set<Layer> ignoreLayerSet;
	Vector2 localPosition;	// The position relative to the game object's transform

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	BoxCollider(GameObject* initOwner);
	BoxCollider(GameObject* initOwner, Layer initLayer);
	void Debug();
	void Enable();
	void Disable();
	void OnComponentDestroyed() override;
	bool IsActive() const;
	Bound GetBound();

};