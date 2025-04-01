/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <concepts>
#include <iostream>
#include <random>

#include <SDL.h>

class Transform;

enum class Layer {

	Background,
	Default,
	Bullet,
	Player,
	Zombie,
	GUI,
	Menu,

};

class Vector2 {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	float x, y;

	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Vector2();
	Vector2(float initX, float initY);
	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);
	float Angle() const;
	float Magnitude() const;
	float Dot(const Vector2& other) const;
	Vector2 operator+(const Vector2& other);
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*(const float& other);
	Vector2 operator*(const float& other)const;
	Vector2 operator*=(const float& other);
	Vector2 operator/(const float& other);
	Vector2 operator/(const float& other) const;
	Vector2 operator/=(const float& other);
	Vector2 Normalize();
	Vector2 Rotate(float angleInRadian);
	Vector2 Inverse();

	static float Dot(const Vector2& first, const Vector2& second);
	static Vector2 Lerp(Vector2 from, Vector2 to, float time);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& other);

};

class Math {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

public:

	static constexpr float PI = 3.14159265359f;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	static float Clamp(float value, float lowerBound, float upperBound);
	static float RadToDeg(float angleInRadian);
	static float DegToRad(float angleInDegree);
	static float Fade(float t);
	static float Lerp(float start, float end, float time);
	static Vector2 SDLToC00(Vector2 position, Vector2 scale);
	static Vector2 C00ToSDL(Vector2 position, Vector2 scale);

};

class Random {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static std::mt19937 randomEngine; // Mersenne Twister engine

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	static void Init();
	static int Int(int min, int max);
	static float Float(float min, float max);
	static Vector2 Direction();
	static Vector2 Direction(Vector2 from, Vector2 to);
	
	template <typename T> requires std::is_arithmetic_v<T> static T Sign(T value);

};
#include <Random.inl>

class Bound {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	Vector2 center = Vector2::zero;
	Vector2 extents = Vector2::zero;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	float Top();
	float Left();
	float Bottom();
	float Right();

};

class Color {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

public:

	static const Color TRANSPARENT;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color BLACK;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	Uint8 r, g, b, a;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Color();
	Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA);
	SDL_Color ToSDLColor();

};

class Algorithm {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	static std::vector<int> perlinPermutationTable;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	static float PerlinGrad(int hash, Vector2 v);

public:

	static void PerlinInit();
	static float PerlinNoise(Vector2 v);

	template <typename T> static void Shuffle(std::vector<T>& array);
		
};
#include <Algorithm.inl>

class Align {

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	static void MiddleVertically(Transform* something, Transform* with);
	static void MiddleHorizontally(Transform* something, Transform* with);
	static void Top(Transform* something, Transform* with);
	static void Bottom(Transform* something, Transform* with);
	static void Left(Transform* something, Transform* with);
	static void Right(Transform* something, Transform* with);

};