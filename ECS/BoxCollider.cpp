/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <BoxCollider.h>

#include <GameCore.h>
#include <PhysicsManager.h>
#include <Transform.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

BoxCollider::BoxCollider(GameObject* initOwner) : GameComponent(initOwner) {

	enabled = true;

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	PhysicsManager::Instance()->RegisterBoxCollider(this);

}

BoxCollider::BoxCollider(GameObject* initOwner, Layer initLayer) : GameComponent(initOwner) {

	enabled = true;

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	PhysicsManager::Instance()->RegisterBoxCollider(this);

}

void BoxCollider::Debug() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound = GetBound();
	GameCore::DrawRectangle(bound.center, bound.extents, false, false, Color::GREEN, Owner()->GetLayer());

}

void BoxCollider::Enable() {

	enabled = true;

}

void BoxCollider::Disable() {

	enabled = false;

}

void BoxCollider::OnComponentDestroyed() {

	ignoreLayerSet.clear();

	PhysicsManager::Instance()->UnregisterBoxCollider(this);

}

bool BoxCollider::IsActive() const { return enabled; }

Bound BoxCollider::GetBound() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound;
	bound.center = transform->position + localPosition;
	bound.extents = transform->scale / 2.0f;

	return bound;

}