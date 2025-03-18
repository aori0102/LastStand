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

/*

class Firearm : public GameObject, public Item {

public:

	enum class Attribute {

		Damage,
		ReloadTime,
		MaxAmmo,
		CriticalChance

	};

private:

	std::unordered_map<Attribute, float> baseAttributeMap;
	std::unordered_map<Attribute, float> attributeMultiplierMap;

	int previousCurrentAmmo;
	int previousReserveAmmo;

	int currentAmmo;
	int reserveAmmo;

	float fireRate;		// In rounds per minute

	float shotDelay;	// Delay in seconds between shots
	float lastShotTick;
	bool isReloading;
	float reloadStartTick;

private:

	enum class UIIndex {

		AmmoLabel,
		AmmoFrame,
		AmmoIcon,

	};

	static const std::unordered_map<UIIndex, Vector2> UI_POSITION_MAP;
	static const std::unordered_map<UIIndex, int> UI_FONT_SIZE_MAP;
	static const std::unordered_map<UIIndex, std::string> UI_LABEL_MAP;
	static const std::unordered_map<UIIndex, std::string> UI_TEXT_MAP;

	static const std::string FOLDER_PATH;
	static const std::string FILE_EXTENSION;

	std::unordered_map<UIIndex, GameObject*> uiElementMap;

	void InitializeUI();

public:

	Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime);

	void Reload();

	bool IsReloading() const;
	int CurrentAmmo() const;

	void ModifyAttributeMultiplier(Attribute attribute, float amount);
	float GetAttribute(Attribute attribute);

	void OnDestroy() override;
	bool TryUse(Player* player) override;
	void Update() override;

};

*/

enum class FirearmAttributeIndex {

	Damage,
	ReloadTime,
	CriticalDamageMultiplier,
	CriticalChance,
	Firerate,
	MagazineCapacity,

};

class Firearm : public GameObject {

	/// ----------------------------------
	/// STRUCTURES AND CONSTANTS
	/// ----------------------------------

protected:

	static const std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, float>> BASE_ATTRIBUTE_MAP;

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	float lastReloadTick;
	bool isReloading;

protected:
	
	float reloadTime;
	int magazineCapacity;
	std::unordered_map<FirearmAttributeIndex, float> attributeMultiplierMap;

public:

	float damage;
	float fireRate;
	int currentAmmo;
	int reserveAmmo;

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Firearm();

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

	Pistol();

	bool TryUse(Player* player) override;
	float GetAttribute(FirearmAttributeIndex attributeIndex) override;

};

class Shotgun : public Item, public Firearm {

	/// ----------------------------------
	/// FIELDS
	/// ----------------------------------

private:

	/// ----------------------------------
	/// METHODS
	/// ----------------------------------

public:

	Shotgun();

	bool TryUse(Player* player) override;
	float GetAttribute(FirearmAttributeIndex attributeIndex) override;

};