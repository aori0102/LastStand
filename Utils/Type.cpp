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

Vector2 Vector2::Lerp(Vector2 from, Vector2 to, float time) {

	return Vector2(
		Math::Lerp(from.x, to.x, time),
		Math::Lerp(from.y, to.y, time)
	);

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

Color Math::Temperature(float value) {

	value = Clamp(value, 0.0f, 1.0f);

	if (value <= 0.5f)
		return Color(Lerp(0, 255, value), Lerp(0, 255, value), 255, 255);
	else
		return Color(255, Lerp(0, 255, value), Lerp(0, 255, value), 255);

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

float Math::Fade(float t) {

	return t * t * t * (t * (t * 6 - 15) + 10);

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

Vector2 Random::Direction() {

	float angle = Random::Float(0.0f, 2.0f * Math::PI);

	return Vector2::right.Rotate(angle).Normalize();

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

// --- ALGORITHM ---
std::vector<int> Algorithm::perlinPermutationTable = std::vector<int>(512, 0);

float Algorithm::PerlinGrad(int hash, Vector2 v) {

	int h = hash & 3;	// Select one of 4 gradient directions
	float a = h & 1 ? v.x : -v.x;
	float b = h & 2 ? v.y : -v.y;

	return a + b;

}

void Algorithm::PerlinInit() {

	std::vector<int> p(256);
	for (int i = 0; i < 256; i++)
		p[i] = i;

	Shuffle(p);

	for (int i = 0; i < 256; i++) {

		perlinPermutationTable[i] = p[i];
		perlinPermutationTable[256 + i] = p[i];	// Double array to prevent overflow

	}

}

float Algorithm::PerlinNoise(Vector2 v) {

	// Get integer grid coord
	int x_coord = (int)std::floorf(v.x) & 255;
	int y_coord = (int)std::floorf(v.y) & 255;

	// Get fractional part
	Vector2 fractional(v.x - floorf(v.x), v.y - floorf(v.y));

	// Apply fade function
	float a = Math::Fade(fractional.x);
	float b = Math::Fade(fractional.y);

	// Get gradient hashes for four corner
	int c1 = perlinPermutationTable[x_coord + perlinPermutationTable[y_coord]];
	int c2 = perlinPermutationTable[x_coord + perlinPermutationTable[y_coord + 1]];
	int c3 = perlinPermutationTable[x_coord + 1 + perlinPermutationTable[y_coord]];
	int c4 = perlinPermutationTable[x_coord + 1 + perlinPermutationTable[y_coord + 1]];

	// Compute dot product
	float g1 = PerlinGrad(c1, fractional);
	float g2 = PerlinGrad(c2, fractional + Vector2::left);
	float g3 = PerlinGrad(c3, fractional + Vector2::down);
	float g4 = PerlinGrad(c4, fractional + Vector2::left + Vector2::down);

	// Interpolate
	float lerp_x1 = Math::Lerp(g1, g2, a);
	float lerp_x2 = Math::Lerp(g3, g4, a);
	return Math::Lerp(lerp_x1, lerp_x2, b);

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