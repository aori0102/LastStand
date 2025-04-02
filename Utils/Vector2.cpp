/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
Vector2 Vector2::up = Vector2(0.0f, 1.0f);
Vector2 Vector2::down = Vector2(0.0f, -1.0f);
Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
Vector2 Vector2::right = Vector2(1.0f, 0.0f);

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Vector2::Vector2() : x(0.0f), y(0.0f) {};

Vector2::Vector2(float initX, float initY) : x(initX), y(initY) {};

bool Vector2::operator==(const Vector2& other) {

	return x == other.x && y == other.y;

}

bool Vector2::operator!=(const Vector2& other) {

	return !(*this == other);

}

float Vector2::Angle() const {

	float angle = acos(Dot(*this, Vector2::right) / Magnitude());

	if (y < 0)
		return angle;
	else
		return -angle;

}

float Vector2::Magnitude() const {

	return sqrt(x * x + y * y);

}

float Vector2::Dot(const Vector2& other) const {

	return Dot(*this, other);

}

Vector2 Vector2::operator+(const Vector2& other) {

	Vector2 res(x + other.x, y + other.y);

	return res;

}

Vector2 Vector2::operator+(const Vector2& other) const {

	Vector2 res(x + other.x, y + other.y);

	return res;

}

Vector2 Vector2::operator+=(const Vector2& other) {

	*this = *this + other;

	return *this;

}

Vector2 Vector2::operator-(const Vector2& other) {

	Vector2 res(x - other.x, y - other.y);

	return res;

}

Vector2 Vector2::operator-(const Vector2& other) const {

	Vector2 res(x - other.x, y - other.y);

	return res;

}

Vector2 Vector2::operator-=(const Vector2& other) {

	*this = *this - other;

	return *this;

}

Vector2 Vector2::operator*(const float& other) {

	Vector2 res(x * other, y * other);

	return res;

}

Vector2 Vector2::operator*(const float& other) const {

	Vector2 res(x * other, y * other);

	return res;

}

Vector2 Vector2::operator*=(const float& other) {

	*this = *this * other;

	return *this;

}

Vector2 Vector2::operator/(const float& other) {

	if (other == 0.0f)
		throw std::exception("Vector2 division by zero");

	Vector2 res(x / other, y / other);

	return res;

}

Vector2 Vector2::operator/(const float& other) const {

	Vector2 res(x / other, y / other);

	return res;

}

Vector2 Vector2::operator/=(const float& other) {

	*this = *this / other;

	return *this;

}

Vector2 Vector2::Normalize() {

	float magnitude = Magnitude();

	if (magnitude == 0.0f)
		return *this;

	return Vector2(x / magnitude, y / magnitude);

}

Vector2 Vector2::Rotate(float angleInRadian) {

	Vector2 res(
		x * std::cosf(angleInRadian) - y * std::sinf(angleInRadian),
		x * std::sinf(angleInRadian) + y * std::cosf(angleInRadian)
	);

	return res;

}

Vector2 Vector2::Inverse() {

	return Vector2(-x, -y);

}

float Vector2::Dot(const Vector2& first, const Vector2& second) {

	return first.x * second.x + first.y * second.y;

}

Vector2 Vector2::Lerp(Vector2 from, Vector2 to, float time) {

	return Vector2(
		Math::Lerp(from.x, to.x, time),
		Math::Lerp(from.y, to.y, time)
	);

}

std::ostream& operator<<(std::ostream& os, const Vector2& other) {

	os << "(" << other.x << ", " << other.y << ")";

	return os;

}