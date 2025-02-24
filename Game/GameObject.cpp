#include <GameComponent.h>
#include <Game.h>
#include <sstream>
#include <RenderManager.h>

unordered_set<GameObject*> GameObject::deletionSet = {};
int GameObject::currentID = 0;

GameObject::GameObject() {

	name = "Game Object";
	layer = Layer::Default;
	id = GameObject::GetNextID();

	AddComponent<Transform>();

	Game::RegisterGameObject(this);
	RenderManager::UpdateRenderObject(this);

	Render = []() {};

}

void GameObject::SetLayer(Layer newLayer) {

	layer = newLayer;

	RenderManager::UpdateRenderObject(this);

}

GameObject::GameObject(string initName) {

	name = initName;
	id = GameObject::GetNextID();
	layer = Layer::Default;

	AddComponent<Transform>();

	Game::RegisterGameObject(this);
	RenderManager::UpdateRenderObject(this);

	Render = []() {};

}

GameObject::GameObject(string initName, Layer initLayer) {

	name = initName;
	layer = initLayer;
	id = GameObject::GetNextID();

	AddComponent<Transform>();

	Game::RegisterGameObject(this);
	RenderManager::UpdateRenderObject(this);

	Render = []() {};

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

	if ((int)a->layer == (int)b->layer)
		return a->id < b->id;
	else
		return (int)a->layer < (int)b->layer;

}

int GameObject::ID() { return id; }

int GameObject::GetNextID() { return ++currentID; }

void GameObject::Enable() {

	enabled = true;

}

void GameObject::Disable() {

	enabled = false;

}

bool GameObject::IsActive() { return enabled; }