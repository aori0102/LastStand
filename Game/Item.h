#pragma once

#include <GameComponent.h>

class Player;
class Item {

public:

	virtual void Use(Player* user) = 0;

};

class Firearm : public GameObject, public Item {

private:

	float damage;
	int ammoCapacity;
	int currentAmmo;
	float fireRate;		// In rounds per minute
	float reloadTime;

	float shotDelay;	// Delay in seconds between shots
	float lastShotTick;
	bool isReloading;
	float reloadStartTick;

public:

	Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime);

	void Use(Player* player) override;
	void Update() override;
	void Reload();

	bool IsReloading() const;
	float GetReloadingProgress() const;
	int GetCurrentAmmo() const;

};