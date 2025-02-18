#include <GameComponent.h>
#include <Game.h>

unordered_set<GameObject*> GameObject::deletionSet = {};

GameObject* GameComponent::Owner() {

	return owner;

}

GameObject::GameObject() {

	name = "Game Object";

	AddComponent<Transform>();

	Game::RegisterGameObject(this);

}

GameObject::GameObject(string initName) {

	name = initName;

}

GameObject::~GameObject() {

	// Clean up components
	auto it = componentMap.begin();
	while (it != componentMap.end()) {

		(it->second)->OnComponentDestroyed();

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

void GameObject::CleanUpCache() {
	// Clean up objects those are to be deleted

	auto it = deletionSet.begin();

	while (it != deletionSet.end()) {

		(*it)->OnDestroy();

		delete (*it);

		it++;

	}

	deletionSet.clear();

}

void GameObject::Update() {}

void GameObject::OnDestroy() {}

void GameObject::OnCollisionEnter(BoxCollider* other) {}

void GameObject::OnCollisionExit(BoxCollider* other) {}