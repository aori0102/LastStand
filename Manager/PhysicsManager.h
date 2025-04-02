/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>
#include <unordered_set>

#include <Utils.h>

class Bound;
class BoxCollider;
class GameObject;
class RigidBody;

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

	std::unordered_set<BoxCollider*> boxColliderSet;	// Reference to all colliders in game
	std::unordered_set<RigidBody*> rigidBodySet;		// Reference to all rigid bodies in game
	std::unordered_map<BoxCollider*, std::unordered_set<BoxCollider*>> colliderHitMap;

	static PhysicsManager* instance;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	PhysicsManager();
	~PhysicsManager();
	void Update();
	void RegisterBoxCollider(BoxCollider* boxCollider);
	void UnregisterBoxCollider(BoxCollider* boxCollider);
	void RegisterRigidBody(RigidBody* rigidBody);
	void UnregisterRigidBody(RigidBody* rigidBody);
	void LateCollisionCall();
	bool BoxCast(BoxCollider* collider, Vector2 movementVector, HitInfo* hitInfo = nullptr);
	bool RayCast(Vector2 origin, Vector2 end, HitInfo* hitInfo = nullptr);
	bool ClipLineRectangle(Vector2 start, Vector2 end, Bound bound, Vector2* newStart = nullptr, Vector2* newEnd = nullptr);

	static PhysicsManager* Instance();

};