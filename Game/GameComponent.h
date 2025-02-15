#pragma once

#include <SDL.h>
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

public:

	GameComponent(GameObject* initOwner);

	GameObject* GetOwner();

	virtual void FlushComponent();

};

class GameObject {

private:

	unordered_map<type_index, GameComponent*> componentMap;

	// The queue to delete game objects
	static unordered_set<GameObject*> deletionSet;

public:

	string name;

	GameObject();
	~GameObject();

	virtual void Update();

	virtual void OnDestroy();

	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

	template<class T>
	T* GetComponent();

	template<class T>
	T* AddComponent();

	static void ObjectUpdate();

	static void Destroy(GameObject* gameObject);

};
#include "GameComponent.inl"

enum class ImageFill {

	Horizontal,
	Vertical,
	None,

};

class Image : public GameComponent {

private:

	SDL_Texture* texture;

	Vector2 imageDimension;	// Original image's dimension

public:

	Vector2 position;
	Vector2 size;
	Vector2 pivot;
	float angle;
	float fillAmount;

	ImageFill imageFill;

	Image(GameObject* initOwner);
	~Image();

	bool LoadImage(string path);

	void Render();

	void FreeImage();

};

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

public:

	Layer layer;
	Vector2 localPosition;	// The position relative to the game object's transform

	BoxCollider(GameObject* initOwner);

	void Debug();

	Bound GetBound();

	void FlushComponent() override;

};

class Humanoid : public GameComponent {

private:

	float health;
	float maxHealth;

public:

	Humanoid(GameObject* initOwner);

	void SetMaxHealth(float newMaxHealth);
	float GetHealth();
	float GetMaxHealth();

	void Damage(float amount);

};

class Inventory : public GameComponent {

private:

	Item* holdingItem;

public:

	Inventory(GameObject* initOwner);

	void AddItem(Item* newItem);
	void UseCurrent(Player* player);
	Item* GetCurrentItem();

};