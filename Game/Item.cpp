#include <Item.h>
#include <Player.h>
#include <Projectile.h>
#include <Game.h>
#include <PlayerUI.h>

const float BULLET_VELOCITY = 7000.0f;

Firearm::Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime) {

	// Base
	baseAttributeMap[Attribute::Damage] = initDamage;
	baseAttributeMap[Attribute::ReloadTime] = initReloadTime;
	baseAttributeMap[Attribute::AmmoCapacity] = initAmmoCapacity;
	currentAmmo = initAmmoCapacity;
	fireRate = initFireRate;

	// Multiplier
	attributeMultiplierMap[Attribute::Damage] = 1.0f;
	attributeMultiplierMap[Attribute::ReloadTime] = 1.0f;
	attributeMultiplierMap[Attribute::AmmoCapacity] = 1.0f;

	shotDelay = 60.0f / fireRate;
	lastShotTick = 0.0f;
	isReloading = false;
	reloadStartTick = 0.0f;

	reloadUI = new ReloadUI(this);
	firearmUI = new FirearmUI(this);

	firearmUI->GetComponent<Transform>()->position = Vector2(700.0f, 700.0f);

}

Firearm::~Firearm() {

	delete reloadUI;
	reloadUI = nullptr;

	delete firearmUI;
	firearmUI = nullptr;

}

bool Firearm::Use(Player* player) {

	// Player is invalid
	if (!player)
		return false;

	// Ammo is insufficient
	if (currentAmmo == 0)
		return false;

	// Is reloading
	if (isReloading)
		return false;

	// If is still in the delay
	if (Game::Time() < lastShotTick + shotDelay)
		return false;

	// Get the direction the player is facing
	Vector2 direction = player->Forward();

	// Get player's position
	Vector2 origin = player->GetComponent<Transform>()->position;

	// Fire
	new Projectile(origin, direction, BULLET_VELOCITY, baseAttributeMap[Attribute::Damage] * attributeMultiplierMap[Attribute::Damage]);
	currentAmmo--;
	lastShotTick = Game::Time();

	return true;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	isReloading = true;
	reloadStartTick = Game::Time();
	currentAmmo = baseAttributeMap[Attribute::AmmoCapacity] * attributeMultiplierMap[Attribute::AmmoCapacity];

}

void Firearm::Update() {

	if (isReloading && Game::Time() >= reloadStartTick + baseAttributeMap[Attribute::ReloadTime] * attributeMultiplierMap[Attribute::ReloadTime])
		isReloading = false;

}

bool Firearm::IsReloading() const { return isReloading; }

float Firearm::GetReloadingProgress() {

	float reloadTime = baseAttributeMap[Attribute::ReloadTime] * attributeMultiplierMap[Attribute::ReloadTime];

	if (reloadTime == 0.0f)
		throw new exception("Reload time of firearm is 0s. Why?");

	return ((Game::Time() - reloadStartTick) / reloadTime);

}

int Firearm::CurrentAmmo() const {

	return currentAmmo;

}


void Firearm::ModifyAttributeMultiplier(Attribute attribute, float amount) {

	attributeMultiplierMap[attribute] = amount;

}