/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>
#include <unordered_set>

#include <Type.h>

class GameObject;
class BoxCollider;
class RigidBody;
class Bound;

class HitInfo {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	BoxCollider* thisCollider;
	BoxCollider* otherCollider;
	Vector2 contactPoint;

};

class PhysicsManager {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	// This value is used to set a small margin between objects. To prevent
	// object going through each other due to small calculation difference
	const float MOVEMENT_PERCENTAGE = 0.99f;
	
	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_set<BoxCollider*> boxColliderSet;
	std::unordered_set<RigidBody*> rigidBodySet;
	std::unordered_map<BoxCollider*, std::unordered_set<BoxCollider*>> colliderHitMap;

	static PhysicsManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	PhysicsManager();

	static PhysicsManager* Instance();

	void Update();

	void RegisterBoxCollider(BoxCollider* boxCollider);
	void UnregisterBoxCollider(BoxCollider* boxCollider);

	void RegisterRigidBody(RigidBody* rigidBody);
	void UnregisterRigidBody(RigidBody* rigidBody);

	bool BoxCast(BoxCollider* collider, Vector2 movementVector, HitInfo* hitInfo = nullptr);
	bool RayCast(Vector2 origin, Vector2 end, HitInfo* hitInfo = nullptr);

	bool ClipLineRectangle(Vector2 start, Vector2 end, Bound bound, Vector2* newStart = nullptr, Vector2* newEnd = nullptr);

	void LateCollisionCall();

};