/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

#include <GameCore.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

float Math::Clamp(float value, float lowerBound, float UpperBound) {

	return std::min(std::max(value, lowerBound), UpperBound);

}

float Math::RadToDeg(float angleInRadian) {

	return angleInRadian * 180.0f / PI;

}

float Math::DegToRad(float angleInDegree) {

	return angleInDegree * PI / 180.0f;

}

float Math::Fade(float t) {

	return t * t * t * (t * (t * 6 - 15) + 10);

}

float Math::Lerp(float start, float end, float time) {

	time = Math::Clamp(time, 0.0f, 1.0f);

	return start * (1.0f - time) + end * time;

}

Vector2 Math::SDLToC00(Vector2 position, Vector2 scale) {

	return Vector2(
		position.x - (GameCore::WindowResolution() - scale).x / 2.0f,
		-position.y - (scale - GameCore::WindowResolution()).y / 2.0f
	);

}

Vector2 Math::C00ToSDL(Vector2 position, Vector2 scale) {

	return Vector2(
		position.x - (scale - GameCore::WindowResolution()).x / 2.0f,
		-position.y + (GameCore::WindowResolution() - scale).y / 2.0f
	);

}