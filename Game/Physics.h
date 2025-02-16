#pragma once

#include <unordered_set>
#include <Type.h>

using namespace std;

class GameObject;
class BoxCollider;
class Bound;

class HitInfo {

public:

	BoxCollider* thisCollider;
	BoxCollider* otherCollider;
	Vector2 contactPoint;

};

class Physics {

private:

	static unordered_set<BoxCollider*> boxColliderSet;

public:

	static void RegisterBoxCollider(BoxCollider* boxCollider);
	static void UnregisterBoxCollider(BoxCollider* boxCollider);

	static bool BoxCast(BoxCollider* collider, Vector2 movementVector, HitInfo* hitInfo = nullptr);
	static bool RayCast(Vector2 origin, Vector2 end, HitInfo* hitInfo = nullptr);

	static bool ClipLineRectangle(Vector2 start, Vector2 end, Bound bound, Vector2* newStart = nullptr, Vector2* newEnd = nullptr);

};