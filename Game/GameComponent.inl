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

	return owner->TryGetComponent<T>();

}

template<class T>
bool GameComponent::TryGetComponent(T*& out) {

	return owner->TryGetComponent<T>(out);

}