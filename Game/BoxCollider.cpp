#include <GameComponent.h>
#include <Physics.h>
#include <Game.h>

BoxCollider::BoxCollider(GameObject* initOwner) : GameComponent(initOwner) {

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	Physics::RegisterBoxCollider(this);

}

BoxCollider::BoxCollider(GameObject* initOwner, Layer initLayer) : GameComponent(initOwner) {

	ignoreLayerSet = {};
	localPosition = Vector2::zero;

	Physics::RegisterBoxCollider(this);

}

void BoxCollider::OnComponentDestroyed() {

	Physics::UnregisterBoxCollider(this);

}

void BoxCollider::Debug() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound = GetBound();
	Game::DrawRectangle(bound.center, bound.extents, false, false, Color::GREEN);

}

Bound BoxCollider::GetBound() {

	Transform* transform = Owner()->GetComponent<Transform>();

	Bound bound;
	bound.center = transform->position + localPosition;
	bound.extents = transform->scale / 2.0f;

	return bound;

}