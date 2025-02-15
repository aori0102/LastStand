#include <Item.h>
#include <Player.h>
#include <Projectile.h>
#include <Game.h>

const float BULLET_VELOCITY = 2000.0f;
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
	if (Game::time < lastShotTick + shotDelay)
		return;

	// Get the direction the player is facing
	Vector2 direction = player->GetForward();

	// Get player's position
	Vector2 origin = player->GetComponent<Transform>()->position;

	// Fire
	new Projectile(origin, BULLET_SCALE, direction, BULLET_VELOCITY);
	currentAmmo--;
	lastShotTick = Game::time;
	cout << currentAmmo << " bullet left" << endl;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	isReloading = true;
	reloadStartTick = Game::time;
	currentAmmo = ammoCapacity;

}

void Firearm::Update() {

	if (isReloading && Game::time >= reloadStartTick + reloadTime)
		isReloading = false;

}


bool Firearm::IsReloading() const { return isReloading; }

float Firearm::GetReloadingProgress() const {

	return (Game::time - reloadStartTick / reloadTime);

}