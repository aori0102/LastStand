/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameComponent.h>

#include <set>
#include <sstream>

#include <GameCore.h>
#include <GameManager.h>
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

	deletionSet.clear();

}

void GameObject::UpdateAll() {

	for (auto gameObject : gameObjectSet) {

		//std::cout << "Updating " << gameObject->name << " (" << gameObject << ")\n";

		gameObject->UpdateComponents();
		gameObject->Update();

		//std::cout << "YES\n";

	}

}

void GameObject::DropNuke() {

	for (auto obj : gameObjectSet) {

		Destroy(obj);

	}
	
	CleanUpDeleted();

}

void GameObject::SetLayer(Layer newLayer) {

	layer = newLayer;

	RenderManager::Instance()->UpdateRenderObject(this);

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
	transform = AddComponent<Transform>();

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

	std::cout << "Destructing " << name << " (" << this << ")\n";

	// Clean up components
	auto it = componentMap.begin();
	while (it != componentMap.end()) {

		if (dynamic_cast<Transform*>(it->second))
			std::cout << "Deleting Transform\n";
		else if (dynamic_cast<BoxCollider*>(it->second))
			std::cout << "Deleting BoxCollider\n";
		else if (dynamic_cast<Humanoid*>(it->second))
			std::cout << "Deleting Humanoid\n";
		else if (dynamic_cast<Inventory*>(it->second))
			std::cout << "Deleting Inventory\n";
		else if (dynamic_cast<AnimationController*>(it->second))
			std::cout << "Deleting AnimationController\n";
		else if (dynamic_cast<RigidBody*>(it->second))
			std::cout << "Deleting RigidBody\n";

		std::cout << "OnComponentDestroyed\n";

		(it->second)->OnComponentDestroyed();

		std::cout << "Deleting\n";

		delete it->second;
		it->second = nullptr;

		std::cout << "Incrementing\n";

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