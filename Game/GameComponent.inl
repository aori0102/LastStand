#include <GameComponent.h>

template <class T>
T* GameComponent::GetComponent() {

	return owner->GetComponent<T>();

}

template <class T>
T* GameComponent::AddComponent() {

	return owner->AddComponent<T>();

}

template<class T>
bool GameComponent::TryGetComponent() {

	T* component = GetComponent<T>();

	return component != nullptr;

}

template<class T>
bool GameComponent::TryGetComponent(T* out) {

	out = GetComponent<T>();

	return out != nullptr;

}