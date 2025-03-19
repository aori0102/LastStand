#pragma once

#include <iostream>
#include <random>
#include <concepts>

#include <SDL.h>

class Vector2 {

public:

	static Vector2 zero;
	static Vector2 up;
	static Vector2 down;
	static Vector2 left;
	static Vector2 right;
	float x, y;

	Vector2();
	Vector2(float initX, float initY);

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

	friend std::ostream& operator<<(std::ostream& os, const Vector2& other);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);

	Vector2 Normalize();
	Vector2 Rotate(float angleInRadian);
	Vector2 Inverse();
	float Magnitude() const;
	float Dot(const Vector2& other) const;
	static float Dot(const Vector2& first, const Vector2& second);

	float Angle();

};

class Math {

public:

	static constexpr float PI = 3.14159265359f;

	static float Clamp(float value, float lowerBound, float upperBound);
	static float RadToDeg(float angleInRadian);
	static float DegToRad(float angleInDegree);
	static Vector2 SDLToC00(Vector2 position, Vector2 scale);
	static Vector2 C00ToSDL(Vector2 position, Vector2 scale);

	static float Lerp(float start, float end, float time);

};

class Random {
private:

	static std::mt19937 randomEngine; // Mersenne Twister engine

public:

	static void Init();

	static int Int(int min, int max);

	static float Float(float min, float max);

	template <typename T>
	requires std::is_arithmetic_v<T>
	static T Sign(T value);

};

class Bound {

public:

	Vector2 center = Vector2::zero;
	Vector2 extents = Vector2::zero;

	float Top();
	float Left();
	float Bottom();
	float Right();

};

class Color {

public:

	Uint8 r, g, b, a;

	Color();
	Color(Uint8 initR, Uint8 initG, Uint8 initB, Uint8 initA);

	SDL_Color ToSDLColor();

	static const Color TRANSPARENT;
	static const Color WHITE;
	static const Color RED;
	static const Color GREEN;
	static const Color BLUE;
	static const Color YELLOW;
	static const Color BLACK;

};

class Algorithm {

public:

	template <typename T>
	static void Shuffle(std::vector<T>& array);

};
#include <../Utils/Type.inl>

enum class Layer {

	Background,
	Default,
	Bullet,
	Player,
	Zombie,
	GUI,
	Menu,

};