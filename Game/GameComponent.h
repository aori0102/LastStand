#pragma once

#include <Type.h>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <set>

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

	Transform* transform;

	virtual void OnComponentDestroyed();

	template<class T>
	T* GetComponent();

	template<class T>
	bool TryGetComponent();

	template<class T>
	bool TryGetComponent(T*& out);

	template<class T>
	T* AddComponent();

};

class GameObject {

private:

	std::unordered_map<std::type_index, GameComponent*> componentMap;

	// The set to delete game objects
	static std::unordered_set<GameObject*> deletionSet;

	Layer layer;

	int id;

	static int currentID;

	bool enabled;

protected:

	void SetLayer(Layer newLayer);

public:

	std::string name;

	GameObject();
	GameObject(std::string initName);
	GameObject(std::string initName, Layer initLayer);
	virtual ~GameObject();

	Transform* transform;

	int ID();

	virtual void Update();

	virtual void OnDestroy();

	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

	Layer GetLayer() const { return layer; }

	void Enable();
	void Disable();
	bool IsActive();

	std::function<void()> Render;

	static bool CompareByLayer(const GameObject* a, const GameObject* b);

	static int GetNextID();

	template<class T>
	T* GetComponent();

	template<class T>
	bool TryGetComponent();

	template<class T>
	bool TryGetComponent(T*& out);

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

public:

	std::set<Layer> ignoreLayerSet;

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
	float maxHealth;

	float stamina;
	float maxStamina;

public:

	std::function<void()> OnDeath;

public:

	Humanoid(GameObject* initOwner);

	float GetHealth() const;
	float GetMaxHealth() const;

	float GetStamina() const;
	float GetMaxStamina() const;

	void SetHealth(float amount);

	void Damage(float amount);
	void Heal(float amount);

	void DrainStamina(float amount);
	void GainStamina(float amount);

};

class RigidBody : public GameComponent {

private:

	Vector2 initialForce;

	float lastUpdateTick;

public:

	float mass;
	float drag;

	Vector2 momentum;

public:

	RigidBody(GameObject* initOwner);

	void AddForce(Vector2 force);
	void Update();

	Vector2 GetAcceleration();

	void OnComponentDestroyed() override;

};