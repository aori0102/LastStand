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
	bool Use(Player* player) override;
	void Update() override;

};