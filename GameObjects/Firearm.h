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

	static std::unordered_map<ItemIndex, FirearmInfo> firearmInfoMap;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void HandleReloading();
	void InitializeUI();

protected:

	void ShowUI();
	void HideUI();
	void OnShoot();
	bool CanShoot();
	bool IsCrit();

public:

	Firearm();
	virtual ~Firearm();
	void Reload();
	void UpdateReserveLabel();
	void UpdateCurrentLabel();
	void SetIndex(ItemIndex itemIndex) override;
	void Equip() override;
	void Dequip() override;
	void Update() override;
	bool TryAddToStack(int amount = 1) override;
	bool TryRemoveFromStack(int amount = 1) override;
	bool ItemRanOut() override;
	float GetAttribute(FirearmAttributeIndex attributeIndex);
	ItemIndex GetAmmoItemIndex();
	std::string GetName() const;

	static void ModifyAttributeMultiplier(ItemIndex firearmIndex, FirearmAttributeIndex attributeIndex, float amount);
	static void ResetAttribute();

};

class Pistol : public Firearm {

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void SetIndex(ItemIndex initItemIndex) override;

public:

	bool TryUse() override;

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

private:

	void SetIndex(ItemIndex initItemIndex) override;

public:

	bool TryUse() override;

};

class Rifle : public Firearm {

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

private:

	void SetIndex(ItemIndex initItemIndex) override;

public:

	bool TryUse() override;

};