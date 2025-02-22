#include <GameComponent.h>
#include <Game.h>
#include <sstream>
#include <RenderManager.h>

unordered_set<GameObject*> GameObject::deletionSet = {};
int GameObject::currentID = 0;

GameObject::GameObject() {

	name = "Game Object";
	layer = Layer::Default;

	AddComponent<Transform>();

	Game::RegisterGameObject(this);
	RenderManager::UpdateRenderObject(this);

	id = GameObject::GetNextID();

}

void GameObject::SetLayer(Layer newLayer) {

	layer = newLayer;

	RenderManager::UpdateRenderObject(this);

}

GameObject::GameObject(string initName) {

	name = initName;

	AddComponent<Transform>();

	Game::RegisterGameObject(this);
	RenderManager::UpdateRenderObject(this);

	id = GameObject::GetNextID();

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
		RenderManager::RemoveRenderObject(*it);

		delete (*it);

		it++;

	}

	deletionSet.clear();

}

void GameObject::Update() {}

void GameObject::OnDestroy() {}

void GameObject::OnCollisionEnter(BoxCollider* other) {}

void GameObject::OnCollisionExit(BoxCollider* other) {}

bool GameObject::CompareByLayer(const GameObject* a, const GameObject* b) {

	return (int)a->layer == (int)b->layer
		? a->id < b->id
		: (int)a->layer < (int)b->layer;

}

void GameObject::Render() {}

int GameObject::ID() { return id; }

int GameObject::GetNextID() { return ++currentID; }