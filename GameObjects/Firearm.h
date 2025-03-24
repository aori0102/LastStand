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

enum class FirearmID {

	M1911,
	Beretta1301,

};

enum class ReloadType {

	Magazine,
	PerAmmo,

};

class Firearm : public GameObject {

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

	static const std::unordered_map<FirearmID, std::unordered_map<FirearmAttributeIndex, float>> BASE_ATTRIBUTE_MAP;
	static const std::unordered_map<FirearmID, MediaObject> FIREARM_ICON_INDEX_MAP;
	static const std::unordered_map<FirearmID, std::string> FIREARM_NAME_MAP;

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
	FirearmID firearmID;
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

	Firearm(FirearmID initFirearmID);

	void Update() override;
	void ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount);
	void Reload();
	float GetAttribute(FirearmAttributeIndex attributeIndex);
	std::string GetName() const;
	FirearmID GetFirearmID() const;
	Sprite* GetIconSprite() const;

};

class Pistol : public Item, public Firearm {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Pistol(FirearmID initFirearmID);

	bool TryUse(Player* player) override;

};

class Shotgun : public Item, public Firearm {

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

	Shotgun(FirearmID initFirearmID);

	bool TryUse(Player* player) override;

};