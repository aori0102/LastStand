#include <Type.h>
#include <SDL.h>
#include <GameCore.h>
#include <GameComponent.h>

Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
Vector2 Vector2::up = Vector2(0.0f, 1.0f);
Vector2 Vector2::down = Vector2(0.0f, -1.0f);
Vector2 Vector2::left = Vector2(-1.0f, 0.0f);
Vector2 Vector2::right = Vector2(1.0f, 0.0f);

Vector2::Vector2() : x(0.0f), y(0.0f) {};

Vector2::Vector2(float initX, float initY) : x(initX), y(initY) {};

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

std::ostream& operator<<(std::ostream& os, const Vector2& other) {

	os << "(" << other.x << ", " << other.y << ")";

	return os;

}

float Math::Clamp(float value, float lowerBound, float UpperBound) {

	return std::min(std::max(value, lowerBound), UpperBound);

}

float Math::RadToDeg(float angleInRadian) {

	return angleInRadian * 180.0f / PI;

}

float Math::DegToRad(float angleInDegree) {

	return angleInDegree * PI / 180.0f;

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

float Math::Lerp(float start, float end, float time) {

	time = Math::Clamp(time, 0.0f, 1.0f);

	return start * (1.0f - time) + end * time;

}

std::mt19937 Random::randomEngine = std::mt19937(std::random_device{}());

float Random::Float(float min, float max) {

	std::uniform_real_distribution<float> dist(min, max);
	return dist(randomEngine);

}

void Random::Init() {

	randomEngine.seed(time(nullptr));

}

int Random::Int(int min, int max) {

	std::uniform_int_distribution<int> dist(min, max);
	return dist(randomEngine);

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