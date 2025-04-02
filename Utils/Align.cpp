/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

#include <GameComponent.h>

/// ----------------------------------
/// METHODS
/// ----------------------------------

void Align::MiddleVertically(Transform* something, Transform* with) {

	something->position.y = with->position.y;

}

void Align::MiddleHorizontally(Transform* something, Transform* with) {

	something->position.x = with->position.x;

}

void Align::Top(Transform* something, Transform* with) {

	something->position.y = with->position.y + (with->scale - something->scale).y / 2.0f;

}

void Align::Bottom(Transform* something, Transform* with) {

	something->position.y = with->position.y - (with->scale - something->scale).y / 2.0f;

}

void Align::Left(Transform* something, Transform* with) {

	something->position.x = with->position.x - (with->scale - something->scale).x / 2.0f;

}

void Align::Right(Transform* something, Transform* with) {

	something->position.x = with->position.x + (with->scale - something->scale).x / 2.0f;

}