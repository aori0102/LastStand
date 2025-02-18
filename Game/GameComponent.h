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

class GameObject {

private:

	unordered_map<type_index, GameComponent*> componentMap;

	// The set to delete game objects
	static unordered_set<GameObject*> deletionSet;

public:

	string name;

	GameObject();
	GameObject(string initName);
	~GameObject();

	virtual void Update();

	virtual void OnDestroy();

	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

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

enum class Layer {

	Default,
	Player,
	Enemy

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

class Inventory : public GameComponent {

private:

	Item* holdingItem;

public:

	Inventory(GameObject* initOwner);

	void AddItem(Item* newItem);
	void UseCurrent(Player* player);
	Item* HoldingItem();

};