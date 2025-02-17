#include <Type.h>
#include <SDL.h>

Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
Vector2 Vector2::up = Vector2(0.0f, -1.0f);
Vector2 Vector2::down = Vector2(0.0f, 1.0f);
Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
Vector2 Vector2::right = Vector2(1.0f, 0.0f);

Vector2::Vector2() : x(0.0f), y(0.0f) {};

Vector2::Vector2(float initX, float initY) : x(initX), y(initY) {};

Vector2 Vector2::operator+(const Vector2& other) {

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

Vector2 Vector2::operator-=(const Vector2& other) {

	*this = *this - other;

	return *this;

}

Vector2 Vector2::operator*(const float& other) {

	Vector2 res(x * other, y * other);

	return res;

}

Vector2 Vector2::operator*=(const float& other) {

	*this = *this * other;

	return *this;

}

Vector2 Vector2::operator/(const float& other) {

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

float Vector2::Magnitude() const {

	return sqrt(x * x + y * y);

}

float Vector2::Angle() {

	float angle = acos(Dot(*this, Vector2::right) / Magnitude());

	if (y < 0)
		return angle;
	else
		return -angle;

}

float Vector2::Dot(const Vector2& first, const Vector2& second) {

	return first.x * second.x + first.y * second.y;

}

float Vector2::Dot(const Vector2& other) const {

	return Dot(*this, other);

}

bool Vector2::operator==(const Vector2& other) {

	return x == other.x && y == other.y;

}

bool Vector2::operator!=(const Vector2& other) {

	return !(*this == other);

}

Vector2 Vector2::Inverse() {

	return Vector2(-x, -y);

}

float Math::Clamp(float value, float lowerBound, float UpperBound) {

	return min(max(value, lowerBound), UpperBound);

}

float Math::RadToDeg(float angleInRadian) {

	return angleInRadian * 180.0f / PI;

}

float Math::DegToRad(float angleInDegree) {

	return angleInDegree * PI / 180.0f;

}

float Bound::Top() {

	return (center - extents).y;

}

float Bound::Left() {

	return (center - extents).x;

}

float Bound::Bottom() {

	return (center + extents).y;

}

float Bound::Right() {

	return (center + extents).x;

}

// Colors
const Color Color::TRANSPARENT = Color(0, 0, 0, 0);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::YELLOW = Color(255, 255, 0, 255);
const Color Color::BLACK = Color(0, 0, 0, 255);

Color::Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA) {

	r = initR;
	g = initG;
	b = initB;
	a = initA;

}

Color::Color()
	: r(255), g(255), b(255), a(255) {}

SDL_Color Color::ToSDLColor() {

	return { r, g, b, a };

}