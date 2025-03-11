#include <GameComponent.h>
#include <PhysicsManager.h>
#include <GameCore.h>

BoxCollider::BoxCollider(GameObject* initOwner) : GameComponent(initOwner) {

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	PhysicsManager::Instance()->RegisterBoxCollider(this);

}

BoxCollider::BoxCollider(GameObject* initOwner, Layer initLayer) : GameComponent(initOwner) {

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	PhysicsManager::Instance()->RegisterBoxCollider(this);

}

void BoxCollider::OnComponentDestroyed() {

	PhysicsManager::Instance()->UnregisterBoxCollider(this);

}

void BoxCollider::Debug() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound = GetBound();
	GameCore::DrawRectangle(bound.center, bound.extents, false, false, Color::GREEN, Owner()->GetLayer());

}

Bound BoxCollider::GetBound() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound;
	bound.center = transform->position + localPosition;
	bound.extents = transform->scale / 2.0f;

	return bound;

}