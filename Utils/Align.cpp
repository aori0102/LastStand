/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

#include <GameCore.h>
#include <Transform.h>

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

void Align::MiddleVertically(Transform* something) {

	something->position.y = 0.0f;

}

void Align::MiddleHorizontally(Transform* something) {

	something->position.x = 0.0f;

}

void Align::Top(Transform* something) {

	something->position.y = (GameCore::WindowResolution() - something->scale).y / 2.0f;

}

void Align::Bottom(Transform* something) {

	something->position.y = (something->scale - GameCore::WindowResolution()).y / 2.0f;

}

void Align::Left(Transform* something) {

	something->position.x = (something->scale - GameCore::WindowResolution()).x / 2.0f;

}

void Align::Right(Transform* something) {

	something->position.x = (GameCore::WindowResolution() - something->scale).x / 2.0f;

}