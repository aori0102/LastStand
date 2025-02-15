#include <GameComponent.h>
#include <Game.h>
#include <Physics.h>

unordered_set<GameObject*> GameObject::deletionSet = {};

GameComponent::GameComponent(GameObject* initOwner) {

	if (!initOwner)
		throw new exception("Initialize game component with NULL game object");

	owner = initOwner;

}

void GameComponent::FlushComponent() {}

GameObject* GameComponent::GetOwner() {

	return owner;

}

GameObject::GameObject() {

	name = "Game Object";

	AddComponent<Transform>();

	Game::RegisterGameObject(this);

}

GameObject::~GameObject() {

	// Clean up components
	auto it = componentMap.begin();
	while (it != componentMap.end()) {

		(it->second)->FlushComponent();

		delete it->second;
		it->second = nullptr;

		it++;

	}
	componentMap.clear();

	// Remove game object
	Game::UnregisterGameObject(this);

	OnDestroy();

}

void GameObject::Destroy(GameObject* gameObject) {

	deletionSet.insert(gameObject);

}

void GameObject::ObjectUpdate() {

	auto it = deletionSet.begin();

	while (it != deletionSet.end()) {

		delete* it;

		it++;

	}

	deletionSet.clear();

}

void GameObject::Update() {}

void GameObject::OnDestroy() {}

void GameObject::OnCollisionEnter(BoxCollider* other) {}

void GameObject::OnCollisionExit(BoxCollider* other) {}

BoxCollider::BoxCollider(GameObject* initOwner) : GameComponent(initOwner) {

	layer = Layer::Default;
	localPosition = Vector2::zero;

	Physics::RegisterBoxCollider(this);

}

void BoxCollider::FlushComponent() {

	Physics::UnregisterBoxCollider(this);

}

void BoxCollider::Debug() {

	Game::SetRenderDrawColor(Color::GREEN);
	Transform* transform = GetOwner()->GetComponent<Transform>();
	SDL_FRect quad = {
		transform->position.x + localPosition.x - transform->scale.x / 2.0f,
		transform->position.y + localPosition.y - transform->scale.y / 2.0f,
		transform->scale.x,
		transform->scale.y
	};

	SDL_RenderDrawRectF(Game::gRenderer, &quad);

}

Bound BoxCollider::GetBound() {

	Transform* transform = GetOwner()->GetComponent<Transform>();

	Bound bound;
	bound.center = transform->position + localPosition;
	bound.extents = transform->scale / 2.0f;

	return bound;

}

Transform::Transform(GameObject* initOwner) : GameComponent(initOwner) {

	position = Vector2::zero;
	scale = Vector2(1.0f, 1.0f);

}

void Transform::Translate(Vector2 movementVector, bool tryNavigate) {

	HitInfo hitInfo;
	BoxCollider* collider = GetOwner()->GetComponent<BoxCollider>();

	// Only check for collision if there is a collider
	if (collider && Physics::BoxCast(collider, movementVector, &hitInfo)) {

		// The remaining distance that hasn't been covered
		float remainingDistance = (movementVector - (hitInfo.contactPoint - position)).Magnitude();

		// Assign new position for next check
		position = hitInfo.contactPoint;

		if (!tryNavigate)
			return;

		// Try movement on x axis
		Vector2 movementAlongX = Vector2(movementVector.x, 0.0f).Normalize() * remainingDistance;
		if (Physics::BoxCast(collider, movementAlongX, &hitInfo)) {

			// Try movement on y axis
			Vector2 movementAlongY = Vector2(0.0f, movementVector.y).Normalize() * remainingDistance;
			if (!Physics::BoxCast(collider, movementAlongY, &hitInfo))
				position += movementAlongY;

		} else
			position += movementAlongX;

	} else
		position += movementVector;

}