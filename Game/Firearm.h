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
		MaxAmmo,
		CriticalChance

	};

private:

	std::unordered_map<Attribute, float> baseAttributeMap;
	std::unordered_map<Attribute, float> attributeMultiplierMap;

	int currentAmmo;

	float fireRate;		// In rounds per minute

	float shotDelay;	// Delay in seconds between shots
	float lastShotTick;
	bool isReloading;
	float reloadStartTick;

	// UI
	GameObject* ammoLabel;
	const int AMMO_TEXT_SIZE = 20;

	GameObject* reloadFrame;
	GameObject* reloadBar;
	const Vector2 RELOAD_FRAME_SCALE = Vector2(165.0f, 65.0f);
	const Vector2 RELOAD_BAR_SCALE = Vector2(150.0f, 50.0f);
	const float RELOAD_BAR_BOTTOM_OFFSET = 300.0f;

	float GetReloadingProgress();

public:

	Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime);
	~Firearm();

	bool Use(Player* player) override;
	void Update() override;
	void Reload();

	bool IsReloading() const;
	int CurrentAmmo() const;

	void ModifyAttributeMultiplier(Attribute attribute, float amount);
	float GetAttribute(Attribute attribute);

};