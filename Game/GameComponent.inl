#include <GameComponent.h>

template <class T>
T* GameComponent::GetComponent() {

	return owner->GetComponent<T>();

}

template <class T>
T* GameComponent::AddComponent() {

	return owner->AddComponent<T>();

}