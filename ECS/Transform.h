/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <GameComponent.h>
#include <Utils.h>

class GameObject;

class Transform : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	Vector2 position;
	Vector2 scale;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Transform(GameObject* initOwner);
	void Translate(Vector2 movementVector, bool tryNavigate = true);

};