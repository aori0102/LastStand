#include <Item.h>
#include <Player.h>
#include <Projectile.h>
#include <Game.h>
#include <PlayerUI.h>

const float BULLET_VELOCITY = 7000.0f;
const float BULLET_DAMAGE= 7.89f;
const Vector2 BULLET_SCALE = Vector2(10.0f, 10.0f);

Firearm::Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime) {

	damage = initDamage;
	ammoCapacity = initAmmoCapacity;
	currentAmmo = ammoCapacity;
	fireRate = initFireRate;
	reloadTime = initReloadTime;

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

void Firearm::Use(Player* player) {

	// Player is invalid
	if (!player)
		return;

	// Ammo is insufficient
	if (currentAmmo == 0)
		return;

	// Is reloading
	if (isReloading)
		return;

	// If is still in the delay
	if (Game::Time() < lastShotTick + shotDelay)
		return;

	// Get the direction the player is facing
	Vector2 direction = player->Forward();

	// Get player's position
	Vector2 origin = player->GetComponent<Transform>()->position;

	// Fire
	new Projectile(origin, BULLET_SCALE, direction, BULLET_VELOCITY,BULLET_DAMAGE);
	currentAmmo--;
	lastShotTick = Game::Time();

}

void Firearm::Reload() {

	if (isReloading)
		return;

	isReloading = true;
	reloadStartTick = Game::Time();
	currentAmmo = ammoCapacity;

}

void Firearm::Update() {

	if (isReloading && Game::Time() >= reloadStartTick + reloadTime)
		isReloading = false;

}


bool Firearm::IsReloading() const { return isReloading; }

float Firearm::GetReloadingProgress() const {

	if (reloadTime == 0.0f)
		throw new exception("Reload time of firearm is 0s. Why?");

	return ((Game::Time() - reloadStartTick) / reloadTime);

}

int Firearm::CurrentAmmo() const {

	return currentAmmo;

}