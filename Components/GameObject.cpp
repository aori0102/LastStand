/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameObject.h>
#include <GameComponent.h>

#include <set>
#include <sstream>

#include <GameCore.h>
#include <GameManager.h>
#include <Inventory.h>
#include <RenderManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

int GameObject::currentID = 0;
std::unordered_set<GameObject*> GameObject::deletionSet = {};
std::unordered_set<GameObject*> GameObject::gameObjectSet = {};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void GameObject::CleanUpDeleted() {

	std::unordered_set<GameObject*> toBeDeleted = deletionSet;
	deletionSet.clear();

	for (auto gameObject : toBeDeleted) {

		gameObjectSet.erase(gameObject);
		RenderManager::Instance()->RemoveRenderObject(gameObject);

		delete gameObject;
		gameObject = nullptr;

	}

	toBeDeleted.clear();

}

void GameObject::UpdateAll() {

	for (auto gameObject : gameObjectSet) {

		if (!gameObject->IsActive())
			continue;

		//std::cout << "Updating " << gameObject->name << " (" << gameObject << ")\n";

		gameObject->UpdateComponents();
		gameObject->Update();

		//std::cout << "YES\n";

	}

}

void GameObject::DropNuke() {

	std::cout << "[Janitor] Cleaning game objects..." << std::endl;

	for (auto obj : gameObjectSet) {

		Destroy(obj);

	}

	std::cout << "[Janitor] Total trash: " << gameObjectSet.size() << std::endl;

	for (auto gameObject : deletionSet) {

		std::cout << "[Janitor] Flushing " << gameObject->name << "..." << std::endl;

		gameObjectSet.erase(gameObject);
		RenderManager::Instance()->RemoveRenderObject(gameObject);

		delete gameObject;
		gameObject = nullptr;

		std::cout << "[Janitor] Progress: " << gameObjectSet.size() << " left." << std::endl;

	}

	std::cout << "[Janitor] All done!" << std::endl;
	std::cout << "GameObjectSet has " << gameObjectSet.size() << " item(s) left." << std::endl;

	deletionSet.clear();

}

void GameObject::SetLayer(Layer newLayer) {

	layer = newLayer;

	RenderManager::Instance()->UpdateRenderObject(this);

}

void GameObject::DebugInfo() const {

	std::cout << name << " [" << this << "]" << std::endl;

}

void GameObject::UpdateObjectToDatabase(GameObject* obj) {

	gameObjectSet.insert(obj);
	RenderManager::Instance()->UpdateRenderObject(obj);

}

GameObject::GameObject(std::string initName, Layer initLayer) {

	id = GameObject::GetNextID();
	enabled = true;
	componentMap = {};
	layer = initLayer;

	name = initName;
	if (!Render)
		Render = []() {};
	if (!OnEnabled)
		OnEnabled = []() {};
	if (!OnDisabled)
		OnDisabled = []() {};
	transform = AddComponent<Transform>();

}

int GameObject::ID() const { return id; }

void GameObject::Enable() {

	enabled = true;
	OnEnabled();

}

void GameObject::Disable() {

	enabled = false; 
	OnDisabled();

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

}

void GameObject::Update() {}

void GameObject::OnCollisionEnter(BoxCollider* other) {}

void GameObject::OnCollisionExit(BoxCollider* other) {}

void GameObject::Destroy(GameObject* gameObject) {

	if (!gameObjectSet.contains(gameObject))
		return;

	gameObject->Disable();

	deletionSet.insert(gameObject);

}

int GameObject::GetNextID() { return ++currentID; }

bool GameObject::CompareByLayer(const GameObject* a, const GameObject* b) {

	if ((int)a->layer == (int)b->layer)
		return a->id < b->id;
	else
		return (int)a->layer < (int)b->layer;

}