/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <string>
#include <typeindex>
#include <unordered_set>

#include <Utils.h>

class BoxCollider;
class GameComponent;
class Transform;

class GameObject {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	int id;
	bool enabled;
	std::unordered_map<std::type_index, GameComponent*> componentMap;
	Layer layer;

	static int currentID;
	// The set that stores all game object requested to be deleted
	// by the user
	static std::unordered_set<GameObject*> deletionSet;
	static std::unordered_set<GameObject*> gameObjectSet;
	static std::unordered_set<GameObject*> startObjectSet;

	friend class GameManager;

public:

	std::string name;
	std::function<void()> Render;
	std::function<void()> OnEnabled;
	std::function<void()> OnDisabled;
	Transform* transform;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	static void CleanUpDeleted();
	static void StartAll();
	static void UpdateAll();
	static void DropNuke();

protected:

	void SetLayer(Layer newLayer);
	void DebugInfo() const;

	static void UpdateObjectToDatabase(GameObject* obj);

public:

	GameObject(std::string initName = "Game Object", Layer initLayer = Layer::Default);
	int ID() const;
	void Enable();
	void Disable();
	void UpdateComponents();
	bool IsActive() const;
	Layer GetLayer() const;

	virtual ~GameObject();
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

	template<class T> bool IsA();
	template<class T> bool TryGetComponent();
	template<class T> bool TryGetComponent(T*& out);
	template<class T> T* AddComponent();
	template<class T> T* GetComponent();
	template<class T> T* As();

	static void Destroy(GameObject* gameObject);
	static int GetNextID();
	static bool CompareByLayer(const GameObject* a, const GameObject* b);
	template <class T = GameObject> static T* Instantiate(std::string initName = "Game Object", Layer initLayer = Layer::Default);

};
#include <GameObject.inl>