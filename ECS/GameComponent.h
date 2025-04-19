/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

class GameObject;
class Transform;

class GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	GameObject* owner;

	friend class GameObject;
	friend class GameCore;

public:

	Transform* transform;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

protected:

	GameComponent(GameObject* initOwner);

	virtual void OnComponentDestroyed();
	virtual void OnComponentUpdate();

public:

	GameObject* Owner();

	template<class T> bool TryGetComponent();
	template<class T> bool TryGetComponent(T*& out);
	template<class T> T* GetComponent();
	template<class T> T* AddComponent();

};
#include "GameComponent.inl"