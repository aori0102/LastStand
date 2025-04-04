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

#include <Utils.h>

class AnimationClip;
class AnimationNode;
class BoxCollider;
class GameObject;
class HotBarUI;
class InventoryUI;
class Item;
class Player;
class Transform;
enum class AnimationIndex;
enum class ItemIndex;

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

class GameObject {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	int id;
	bool enabled;
	std::unordered_map<std::type_index, GameComponent*> componentMap;
	Layer layer;

	static int currentID;
	// The set that stores all game object requested to be deleted
	// by the user
	static std::unordered_set<GameObject*> deletionSet;
	static std::unordered_set<GameObject*> gameObjectSet;

	friend class GameManager;

public:

	std::string name;
	std::function<void()> Render;
	Transform* transform;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	static void CleanUpDeleted();
	static void UpdateAll();
	static void DropNuke();

protected:

	void SetLayer(Layer newLayer);

	static void UpdateObjectToDatabase(GameObject* obj);

public:

	GameObject(std::string initName = "Game Object", Layer initLayer = Layer::Default);
	int ID() const;
	void Enable();
	void Disable();
	void UpdateComponents();
	bool IsActive() const;
	Layer GetLayer() const;

	virtual ~GameObject();
	virtual void Update();
	virtual void OnCollisionEnter(BoxCollider* other);
	virtual void OnCollisionExit(BoxCollider* other);

	template<class T> bool IsA();
	template<class T> bool TryGetComponent();
	template<class T> bool TryGetComponent(T*& out);
	template<class T> T* AddComponent();
	template<class T> T* GetComponent();
	template<class T> T* As();

	static void Destroy(GameObject* gameObject);
	static int GetNextID();
	static bool CompareByLayer(const GameObject* a, const GameObject* b);
	template <class T = GameObject> static T* Instantiate(std::string initName = "Game Object", Layer initLayer = Layer::Default);

};
#include "GameObject.inl"
#include "GameComponent.inl"

class Transform : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

public:

	Vector2 position;
	Vector2 scale;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Transform(GameObject* initOwner);
	void Translate(Vector2 movementVector, bool tryNavigate = true);

};

class BoxCollider : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	bool enabled;

public:

	std::set<Layer> ignoreLayerSet;
	Vector2 localPosition;	// The position relative to the game object's transform

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	BoxCollider(GameObject* initOwner);
	BoxCollider(GameObject* initOwner, Layer initLayer);
	void Debug();
	void Enable();
	void Disable();
	void OnComponentDestroyed() override;
	bool IsActive() const;
	Bound GetBound();

};

class Humanoid : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float health;
	float maxHealth;
	float stamina;
	float maxStamina;

public:

	std::function<void()> OnDeath;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Humanoid(GameObject* initOwner);
	void SetHealth(float amount);
	void Damage(float amount);
	void Heal(float amount);
	void DrainStamina(float amount);
	void GainStamina(float amount);
	float GetHealth() const;
	float GetMaxHealth() const;
	float GetStamina() const;
	float GetMaxStamina() const;

};

class RigidBody : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float lastUpdateTick;
	Vector2 initialForce;

public:

	float drag;
	float mass;
	Vector2 momentum;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	RigidBody(GameObject* initOwner);
	void AddForce(Vector2 force);
	void Update();
	void OnComponentDestroyed() override;
	Vector2 GetAcceleration();

};

enum class HotBarSlotIndex {

	None,

	First,
	Second,
	Third,
	Forth,
	Fifth,

};

class Inventory : public GameComponent {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	struct ItemState {
		Item* item;
		HotBarSlotIndex slot;
	};

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<ItemIndex, ItemState*> storage;
	std::unordered_map<HotBarSlotIndex, ItemIndex> hotBar;
	HotBarSlotIndex currentSlotIndex;
	HotBarUI* hotBarUI;
	InventoryUI* inventoryUI;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void OnComponentDestroyed() override;

public:

	Inventory(GameObject* initOwner);
	void AddItem(ItemIndex itemIndex, int amount = 1);
	void SelectSlot(HotBarSlotIndex slotIndex);
	void ToggleInventory();
	void LinkItemToHotBar(HotBarSlotIndex hotBarSlotIndex, ItemIndex itemIndex);
	bool IsSufficient(ItemIndex itemIndex, int amount);
	bool TryRemoveItem(ItemIndex itemIndex, int amount = 1);
	bool TryUseCurrent();
	int GetItemCount(ItemIndex itemIndex);
	ItemIndex GetCurrentItemIndex();
	Item* GetCurrentItem();

	template <class T> std::vector<T*> GetItemListOfType();

};
#include <Inventory.inl>

class AnimationController : public GameComponent {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	std::unordered_map<AnimationIndex, AnimationNode*> animationNodeMap;
	AnimationNode* defaultAnimationNode;
	AnimationNode* currentAnimationNode;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void OnComponentDestroyed() override;
	void OnComponentUpdate() override;

public:

	AnimationController(GameObject* initOwner);
	void AddAnimationClip(AnimationIndex animationIndex, bool isStateMachine = false);
	void AddTransition(AnimationIndex from, AnimationIndex to, std::function<bool()> condition = []() { return true; });
	void MakeDefault(AnimationIndex animationIndex);
	void RenderCurrent(Vector2 position, Vector2 scale, float angle);

};