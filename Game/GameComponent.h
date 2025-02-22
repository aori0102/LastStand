#pragma once

#include <Type.h>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class BoxCollider;
class Transform;
class GameObject;
class Item;
class Player;

class GameComponent {

private:

	GameObject* owner;

protected:

	GameComponent(GameObject* initOwner);

public:

	GameObject* Owner();

	virtual void OnComponentDestroyed();

	template<class T>
	T* GetComponent();

	template<class T>
	T* AddComponent();

};

enum class Layer {

	Background,
	Default,
	Player,
	Zombie,
	GUI,
	Menu,

};

class GameObject {

private:

	unordered_map<type_index, GameComponent*> componentMap;

	// The set to delete game objects
	static unordered_set<GameObject*> deletionSet;

	Layer layer;

	int id;

	static int currentID;

protected:

	void SetLayer(Layer newLayer);

public:

	string name;

	GameObject();
	GameObject(string initName);
	virtual ~GameObject();

	int ID();

	virtual void Update();

	virtual void OnDestroy();

	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

	virtual void Render();

	static bool CompareByLayer(const GameObject* a, const GameObject* b);

	static int GetNextID();

	template<class T>
	T* GetComponent();

	template<class T>
	T* AddComponent();

	template<class T>
	bool IsA();

	static void CleanUpCache();

	static void Destroy(GameObject* gameObject);

};
#include "GameObject.inl"
#include "GameComponent.inl"

class Transform : public GameComponent {

public:

	Transform(GameObject* initOwner);

	Vector2 position;
	Vector2 scale;

	void Translate(Vector2 movementVector, bool tryNavigate = true);

};

class BoxCollider : public GameComponent {

private:

	Layer layer;

public:

	Vector2 localPosition;	// The position relative to the game object's transform

	BoxCollider(GameObject* initOwner);
	BoxCollider(GameObject* initOwner, Layer initLayer);

	void Debug();

	Bound GetBound();

	void OnComponentDestroyed() override;

};

class Humanoid : public GameComponent {

private:

	float health;

public:

	float maxHealth;

	Humanoid(GameObject* initOwner);

	float Health() const;

	void Damage(float amount);
	void Heal(float amount);

};