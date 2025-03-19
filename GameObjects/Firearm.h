/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#pragma once

#include <Item.h>

#include <GameComponent.h>
#include <unordered_map>

class Player;

enum class FirearmAttributeIndex {

	Damage,
	ReloadTime,
	CriticalDamageMultiplier,
	CriticalChance,
	Firerate,
	MagazineCapacity,

};

enum class FirearmID {

	M1911,
	Beretta1301,

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

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	// Logic handling
	float lastReloadTick;
	float lastShootTick;
	bool isReloading;
	FirearmID firearmID;

	// UI
	GameObject* ammoIcon;
	GameObject* ammoFrame;
	GameObject* currentAmmoLabel;
	GameObject* reserveAmmoLabel;

protected:
	
	float reloadTime;
	float damage;
	float fireRate;
	int currentAmmo;
	int reserveAmmo;
	int magazineCapacity;
	std::unordered_map<FirearmAttributeIndex, float> attributeMultiplierMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

protected:

	bool TryShoot();
	void ShowUI();
	void HideUI();

public:

	Firearm(FirearmID initFirearmID);

	void Update() override;
	void ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount);
	void Reload();
	virtual float GetAttribute(FirearmAttributeIndex attributeIndex) = 0;

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
	float GetAttribute(FirearmAttributeIndex attributeIndex) override;

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
	float GetAttribute(FirearmAttributeIndex attributeIndex) override;

};