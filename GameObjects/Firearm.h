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
enum class AmmunitionID;

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

struct FirearmInfo {

	AmmunitionID ammunitionID;
	MediaObject iconIndex;
	ReloadType reloadType;
	std::string name;
	std::unordered_map<FirearmAttributeIndex, float> attributeMap;

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

public:

	static const std::unordered_map<ItemIndex, FirearmInfo> BASE_FIREARM_INFO_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	// Logic handling
	int currentAmmo;
	int previousReverseAmmo;
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
	void UpdateReserveLabel();
	float GetAttribute(FirearmAttributeIndex attributeIndex);
	std::string GetName() const;

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