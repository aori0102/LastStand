#pragma once

#include <cmath>

using namespace std;

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
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator*(const float& other);
	Vector2 operator*=(const float& other);
	Vector2 operator/(const float& other);
	Vector2 operator/=(const float& other);

	bool operator==(const Vector2& other);
	bool operator!=(const Vector2& other);
	
	Vector2 Normalize();
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