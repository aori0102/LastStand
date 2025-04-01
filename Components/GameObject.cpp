/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <set>
#include <sstream>

#include <GameCore.h>
#include <RenderManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

int GameObject::currentID = 0;
std::unordered_set<GameObject*> GameObject::deletionSet = {};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void GameObject::SetLayer(Layer newLayer) {

	layer = newLayer;

	RenderManager::Instance()->UpdateRenderObject(this);

}

GameObject::GameObject() {

	id = GameObject::GetNextID();
	enabled = true;
	componentMap = {};
	layer = Layer::Default;

	name = "Game Object";
	if (!Render)
		Render = []() {};
	transform = AddComponent<Transform>();

	GameCore::RegisterGameObject(this);
	RenderManager::Instance()->UpdateRenderObject(this);

}

GameObject::GameObject(std::string initName) {

	id = GameObject::GetNextID();
	enabled = true;
	componentMap = {};
	layer = Layer::Default;

	name = initName;
	if (!Render)
		Render = []() {};
	transform = AddComponent<Transform>();

	GameCore::RegisterGameObject(this);
	RenderManager::Instance()->UpdateRenderObject(this);

}

GameObject::GameObject(std::string initName, Layer initLayer) {

	id = GameObject::GetNextID();
	enabled = true;
	componentMap = {};
	layer = initLayer;

	name = initName;
	if (!Render)
		Render = []() {};
	transform = AddComponent<Transform>();

	GameCore::RegisterGameObject(this);
	RenderManager::Instance()->UpdateRenderObject(this);

}

int GameObject::ID() const { return id; }

void GameObject::Enable() {

	enabled = true;

}

void GameObject::Disable() {

	enabled = false;

}

void GameObject::UpdateComponents() {

	for (auto it = componentMap.begin(); it != componentMap.end(); it++)
		(it->second)->OnComponentUpdate();

}

bool GameObject::IsActive() const { return enabled; }

Layer GameObject::GetLayer() const { return layer; }

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
	GameCore::UnregisterGameObject(this);

	OnDestroy();

}

void GameObject::Update() {}

void GameObject::OnDestroy() {}

void GameObject::OnCollisionEnter(BoxCollider* other) {}

void GameObject::OnCollisionExit(BoxCollider* other) {}

void GameObject::CleanUpCache() {
	// Clean up objects those are to be deleted

	// This set contains all objects that are deleted this frame
	// to avoid calling OnDestroy() on a deallocated object
	std::set<GameObject*> deletedObjectSet;

	while (!deletionSet.empty()) {

		auto it = deletionSet.begin();

		if (!deletedObjectSet.contains(*it))
			(*it)->OnDestroy();
		RenderManager::Instance()->RemoveRenderObject(*it);

		deletedObjectSet.insert(*it);
		delete (*it);

		deletionSet.erase(it);

	}

}

void GameObject::Destroy(GameObject* gameObject) {

	deletionSet.insert(gameObject);

}

int GameObject::GetNextID() { return ++currentID; }

bool GameObject::CompareByLayer(const GameObject* a, const GameObject* b) {

	if ((int)a->layer == (int)b->layer)
		return a->id < b->id;
	else
		return (int)a->layer < (int)b->layer;

}