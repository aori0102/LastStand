#pragma once

#include <unordered_set>
#include <unordered_map>
#include <Type.h>

class GameObject;
class BoxCollider;
class RigidBody;
class Bound;

class HitInfo {

public:

	BoxCollider* thisCollider;
	BoxCollider* otherCollider;
	Vector2 contactPoint;

};

class Physics {

private:

	static std::unordered_set<BoxCollider*> boxColliderSet;
	static std::unordered_set<RigidBody*> rigidBodySet;

	static std::unordered_map<BoxCollider*, std::unordered_set<BoxCollider*>> colliderHitMap;

public:

	static void Update();

	static void RegisterBoxCollider(BoxCollider* boxCollider);
	static void UnregisterBoxCollider(BoxCollider* boxCollider);

	static void RegisterRigidBody(RigidBody* rigidBody);
	static void UnregisterRigidBody(RigidBody* rigidBody);

	static bool BoxCast(BoxCollider* collider, Vector2 movementVector, HitInfo* hitInfo = nullptr);
	static bool RayCast(Vector2 origin, Vector2 end, HitInfo* hitInfo = nullptr);

	static bool ClipLineRectangle(Vector2 start, Vector2 end, Bound bound, Vector2* newStart = nullptr, Vector2* newEnd = nullptr);

	static void LateCollisionCall();

};