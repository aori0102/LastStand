/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <functional>
#include <iostream>
#include <set>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <Type.h>

class AnimationClip;
class BoxCollider;
class GameObject;
class Item;
class Player;
class Transform;
enum class AnimationIndex;
enum class ItemIndex;

class GameComponent {

private:

	GameObject* owner;

	friend class GameObject;
	friend class GameCore;

protected:

	GameComponent(GameObject* initOwner);

	virtual void OnComponentDestroyed();
	virtual void OnComponentUpdate();

public:

	GameObject* Owner();

	Transform* transform;

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

	void UpdateComponents();

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

	template<class T>
	T* As();

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

enum class InventorySlotIndex {

	None,

	First,
	Second,
	Third,
	Forth,
	Fifth,

};

class Inventory : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<ItemIndex, Item*> storage;
	std::unordered_map<InventorySlotIndex, Item*> hotBar;
	InventorySlotIndex currentSlotIndex;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Inventory(GameObject* initOwner);

	void AddItem(ItemIndex itemIndex);
	void SelectSlot(InventorySlotIndex slotIndex);
	bool TryUseCurrent();
	ItemIndex GetCurrentItemIndex();

};

class AnimationController : public GameComponent {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct AnimationNode;

	struct AnimationTransition {

		AnimationNode* to = nullptr;
		std::function<bool()> condition = []() { return true; };

		AnimationTransition(AnimationNode* initTo, std::function<bool()> initCondition)
			: to(initTo), condition(initCondition) {}

	};

	struct AnimationNode {

		AnimationClip* animationClip = nullptr;
		std::vector<AnimationTransition*> transitionList = {};

		AnimationNode(AnimationClip* initAnimationClip)
			: animationClip(initAnimationClip), transitionList({}) {}

	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	AnimationNode* defaultAnimationNode;
	AnimationNode* currentAnimationNode;

	std::unordered_map<AnimationIndex, AnimationNode*> animationNodeMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void OnComponentUpdate() override;
	void OnComponentDestroyed() override;

public:

	AnimationController(GameObject* initOwner);

	void AddAnimationClip(AnimationIndex animationIndex);
	void AddTransition(AnimationIndex from, AnimationIndex to, std::function<bool()> condition = []() { return true; });
	void MakeDefault(AnimationIndex animationIndex);
	void RenderCurrent(Vector2 position, Vector2 scale, float angle);

};