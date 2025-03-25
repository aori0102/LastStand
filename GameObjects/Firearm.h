/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <unordered_map>

#include <GameComponent.h>
#include <Item.h>

class Player;
class Sprite;
enum class MediaObject;

enum class FirearmAttributeIndex {

	Damage,							// Upgrade
	ReloadTime,						// Perk
	CriticalDamage,					// Upgrade
	CriticalChance,					// Perk
	Firerate,						// Upgrade
	MagazineCapacity,				// Upgrade

};

enum class ReloadType {

	Magazine,
	PerAmmo,

};

class Firearm : public GameObject, public Item {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const int CURRENT_AMMO_LABEL_SIZE;
	static const int RESERVE_AMMO_LABEL_SIZE;
	static const float RESERVE_AMMO_LABEL_OFFSET;
	static const Vector2 AMMO_FRAME_POSTIION;
	static const Vector2 AMMO_ICON_POSTIION;

protected:

	static const std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, float>> BASE_ATTRIBUTE_MAP;
	static const std::unordered_map<ItemIndex, MediaObject> FIREARM_ICON_INDEX_MAP;
	static const std::unordered_map<ItemIndex, std::string> FIREARM_NAME_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	// Logic handling
	float lastReloadTick;
	float lastShootTick;
	bool isReloading;
	bool stopReload;
	std::string firearmName;
	ReloadType reloadType;

	// UI
	GameObject* ammoIcon;
	GameObject* ammoFrame;
	GameObject* currentAmmoLabel;
	GameObject* reserveAmmoLabel;
	GameObject* reloadLabel;

protected:

	int currentAmmo;
	int reserveAmmo;
	std::unordered_map<FirearmAttributeIndex, float> attributeMultiplierMap;
	std::unordered_map<FirearmAttributeIndex, float> attributeMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleReloading();

protected:

	bool TryShoot();
	bool IsCrit();
	void ShowUI();
	void HideUI();

public:

	Firearm(ItemIndex initItemIndex);

	void Update() override;
	void ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount);
	void Reload();
	void Equip() override;
	void Dequip() override;
	float GetAttribute(FirearmAttributeIndex attributeIndex);
	std::string GetName() const;
	Sprite* GetIconSprite() const;

};

class Pistol : public Firearm {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Pistol(ItemIndex initItemIndex);

	bool TryUse(Player* player) override;

};

class Shotgun : public Firearm {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

private:

	static const int PELLET;
	static const float PELLET_SPAN_DEGREE;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Shotgun(ItemIndex initItemIndex);

	bool TryUse(Player* player) override;

};