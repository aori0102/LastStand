#include <GameComponent.h>
#include <type_traits>

template <class T>
T* GameObject::GetComponent() {

	if (!is_base_of<GameComponent, T>::value)
		return nullptr;

	auto it = componentMap.find(typeid(T));

	if (it == componentMap.end())
		return nullptr;
	else
		return static_cast<T*>(componentMap[typeid(T)]);

}

template <class T>
T* GameObject::AddComponent() {

	if (!is_base_of<GameComponent, T>::value)
		return nullptr;

	auto it = componentMap.find(typeid(T));

	T* component = new T(this);

	if (it != componentMap.end())
		return static_cast<T*>(it->second);

	componentMap[typeid(T)] = component;

	return static_cast<T*>(component);

}

template<class T>
bool GameObject::IsA() {

	T* type = dynamic_cast<T*>(this);

	return type != nullptr;

}