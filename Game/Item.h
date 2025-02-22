#pragma once

#include <GameComponent.h>
#include <unordered_map>

class Player;
class ReloadUI;
class FirearmUI;

class Item {

public:

	virtual bool Use(Player* user) = 0;

};

class Firearm : public GameObject, public Item {

public:

	enum class Attribute {

		Damage,
		ReloadTime,
		AmmoCapacity

	};

private:

	unordered_map<Attribute, float> baseAttributeMap;
	unordered_map<Attribute, float> attributeMultiplierMap;

	int currentAmmo;

	float fireRate;		// In rounds per minute

	float shotDelay;	// Delay in seconds between shots
	float lastShotTick;
	bool isReloading;
	float reloadStartTick;

	// UI
	ReloadUI* reloadUI;
	FirearmUI* firearmUI;

public:

	Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime);
	~Firearm();

	bool Use(Player* player) override;
	void Update() override;
	void Reload();

	bool IsReloading() const;
	float GetReloadingProgress();
	int CurrentAmmo() const;

	void ModifyAttributeMultiplier(Attribute attribute, float amount);

};