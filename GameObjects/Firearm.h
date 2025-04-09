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

struct FirearmInfo {

	std::string name;
	std::unordered_map<FirearmAttributeIndex, float> attributeMap;
	ItemIndex ammunitionItemIndex;
	ReloadType reloadType;

};

class Firearm : public Item {

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
	bool isReloading;
	bool stopReload;
	int previousCurrentAmmo;
	float lastReloadTick;
	float lastShootTick;
	std::string firearmName;

	// UI
	GameObject* ammoIcon;
	GameObject* ammoFrame;
	GameObject* currentAmmoLabel;
	GameObject* reserveAmmoLabel;
	GameObject* reloadLabel;

protected:

	std::unordered_map<FirearmAttributeIndex, float> attributeMap;
	ReloadType reloadType;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleReloading();

protected:

	void ShowUI();
	void HideUI();
	void OnShoot();
	bool CanShoot();
	bool IsCrit();

public:

	Firearm();
	virtual ~Firearm();
	void ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount);
	void Reload();
	void UpdateReserveLabel();
	void UpdateCurrentLabel();
	void Equip() override;
	void Dequip() override;
	void Update() override;
	bool TryAddToStack(int amount = 1) override;
	bool TryRemoveFromStack(int amount = 1) override;
	bool ItemRanOut() override;
	float GetAttribute(FirearmAttributeIndex attributeIndex);
	ItemIndex GetAmmoItemIndex();
	std::string GetName() const;

	virtual void SetFirearmItemID(ItemIndex initItemIndex) = 0;

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

	void SetFirearmItemID(ItemIndex initItemIndex) override;
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

	void SetFirearmItemID(ItemIndex initItemIndex) override;
	bool TryUse(Player* player) override;

};

class Rifle : public Firearm {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	void SetFirearmItemID(ItemIndex initItemIndex) override;
	bool TryUse(Player* player) override;

};