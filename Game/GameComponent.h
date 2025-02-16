#pragma once

#include <SDL.h>
#include <Type.h>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <SDL_ttf.h>

using namespace std;

class BoxCollider;
class Transform;
class GameObject;
class Item;
class Player;
class Color;

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

class Texture {

protected:

	SDL_Texture* texture;

	Vector2 textureDimension;

	Texture();

public:

	virtual void Render() = 0;

	void FreeTexture();

	SDL_Texture* GetTexture();
	Vector2 GetTextureDimension();

};

class Image : public GameComponent, public Texture {

public:

	Vector2 pivot;
	float angle;
	float fillAmount;

	ImageFill imageFill;

	Image(GameObject* initOwner);
	~Image();

	bool LoadImage(string path);

	void Render() override;

};

class Text : public GameComponent, public Texture {

private:

	TTF_Font* font;

public:

	Text(GameObject* initOwner);
	~Text();

	bool LoadText(string text, Color color);

	void Render() override;

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