/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <GameObject.h>

#include <type_traits>

#include <BoxCollider.h>
#include <Transform.h>

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

template<class T>
bool GameObject::IsA() {

	T* type = dynamic_cast<T*>(this);

	return type != nullptr;

}

template<class T>
bool GameObject::TryGetComponent() {

	static_assert(std::is_base_of<GameComponent, T>::value, "T must inherit from GameComponent");

	T* component = GetComponent<T>();

	return component != nullptr;

}

template<class T>
bool GameObject::TryGetComponent(T*& out) {

	static_assert(std::is_base_of<GameComponent, T>::value, "T must inherit from GameComponent");

	out = GetComponent<T>();

	return out != nullptr;

}

template <class T>
T* GameObject::AddComponent() {

	static_assert(std::is_base_of<GameComponent, T>::value, "T must inherit from GameComponent");

	if (!std::is_base_of<GameComponent, T>::value)
		return nullptr;

	auto it = componentMap.find(typeid(T));

	if (it != componentMap.end())
		return static_cast<T*>(it->second);

	T* component = new T(this);

	componentMap[typeid(T)] = component;

	return static_cast<T*>(component);

}

template <class T>
T* GameObject::GetComponent() {

	static_assert(std::is_base_of<GameComponent, T>::value, "T must inherit from GameComponent");

	if (!std::is_base_of<GameComponent, T>::value)
		return nullptr;

	auto it = componentMap.find(typeid(T));

	if (it == componentMap.end())
		return nullptr;
	else
		return static_cast<T*>(it->second);

}

template<class T>
T* GameObject::As() {

	return dynamic_cast<T*>(this);

}

template <class T>
T* GameObject::Instantiate(std::string initName, Layer initLayer) {

	static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject!");

	std::cout << "Intantiating game object " << initName << std::endl;

	GameObject* object = new T;
	object->name = initName;
	object->layer = initLayer;

	UpdateObjectToDatabase(object);

	return dynamic_cast<T*>(object);

}