/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

std::mt19937 Random::randomEngine = std::mt19937(std::random_device{}());

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Random::Init() {

	randomEngine.seed(time(nullptr));

}

int Random::Int(int min, int max) {

	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomEngine);

}

float Random::Float(float min, float max) {

	std::uniform_real_distribution<float> dist(min, max);
	return dist(randomEngine);

}

Vector2 Random::Direction() {

	float angle = Random::Float(0.0f, 2.0f * Math::PI);

	return Vector2::right.Rotate(angle).Normalize();

}

Vector2 Random::Direction(Vector2 from, Vector2 to) {

	float fromAngle = from.Angle();
	float toAngle = to.Angle();

	float angle = Random::Float(std::min(fromAngle, toAngle), std::max(fromAngle, toAngle));

	return Vector2::right.Rotate(angle).Normalize();

}