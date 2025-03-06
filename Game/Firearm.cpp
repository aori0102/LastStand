#include <Firearm.h>
#include <Player.h>
#include <Projectile.h>
#include <Game.h>
#include <PlayerUI.h>
#include <Texture.h>
#include <string>

const float BULLET_VELOCITY = 7000.0f;

Firearm::Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime) {

	// Base
	baseAttributeMap[Attribute::Damage] = initDamage;
	baseAttributeMap[Attribute::ReloadTime] = initReloadTime;
	baseAttributeMap[Attribute::MaxAmmo] = initAmmoCapacity;
	currentAmmo = initAmmoCapacity;
	fireRate = initFireRate;

	// Multiplier
	attributeMultiplierMap[Attribute::Damage] = 1.0f;
	attributeMultiplierMap[Attribute::ReloadTime] = 1.0f;
	attributeMultiplierMap[Attribute::MaxAmmo] = 1.0f;

	shotDelay = 60.0f / fireRate;
	lastShotTick = 0.0f;
	isReloading = false;
	reloadStartTick = 0.0f;

	// UI
	// Ammo
	ammoLabel = new GameObject("Ammo label", Layer::GUI);
	Text* ammoLabel_text = ammoLabel->AddComponent<Text>();
	ammoLabel_text->LoadText(to_string(currentAmmo), Color::WHITE, AMMO_TEXT_SIZE);
	ammoLabel_text->showOnScreen = true;
	Transform* ammoLabel_transform = ammoLabel->GetComponent<Transform>();
	ammoLabel_transform->position = (Game::WindowResolution() - ammoLabel_transform->scale) / 2.0f;
	ammoLabel->Render = [this, ammoLabel_text]() {
		ammoLabel_text->LoadText(to_string(currentAmmo), Color::WHITE, AMMO_TEXT_SIZE);
		ammoLabel_text->Render();
		};

	// Reload
	reloadFrame = new GameObject("Reload frame", Layer::GUI);
	Image* reloadFrame_image = reloadFrame->AddComponent<Image>();
	reloadFrame_image->backgroundColor = Color::TRANSPARENT;
	reloadFrame_image->outlineColor = Color::WHITE;
	reloadFrame_image->showOnScreen = true;
	Transform* reloadFrame_transform = reloadFrame->GetComponent<Transform>();
	reloadFrame_transform->scale = RELOAD_FRAME_SCALE;
	reloadFrame_transform->position = Vector2::down * RELOAD_BAR_BOTTOM_OFFSET;
	reloadFrame->Render = [reloadFrame_image]() {
		reloadFrame_image->Render();
		};
	reloadFrame->Disable();

	reloadBar = new GameObject("Reload bar", Layer::GUI);
	Image* reloadBar_image = reloadBar->AddComponent<Image>();
	reloadBar_image->backgroundColor = Color::WHITE;
	reloadBar_image->outlineColor = Color::TRANSPARENT;
	reloadBar_image->showOnScreen = true;
	reloadBar_image->imageFill = ImageFill::Horizontal;
	Transform* reloadBar_transform = reloadBar->GetComponent<Transform>();
	reloadBar_transform->scale = RELOAD_BAR_SCALE;
	reloadBar_transform->position = Vector2::down * RELOAD_BAR_BOTTOM_OFFSET;
	reloadBar->Render = [reloadBar_image]() {
		reloadBar_image->Render();
		};
	reloadBar->Disable();

}

Firearm::~Firearm() {

	delete ammoLabel;
	ammoLabel = nullptr;
	delete reloadFrame;
	reloadFrame = nullptr;
	delete reloadBar;
	reloadBar = nullptr;

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
	new Projectile(player, origin, direction, BULLET_VELOCITY, baseAttributeMap[Attribute::Damage] * attributeMultiplierMap[Attribute::Damage]);
	currentAmmo--;
	lastShotTick = Game::Time();

	return true;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	isReloading = true;
	reloadStartTick = Game::Time();
	currentAmmo = baseAttributeMap[Attribute::MaxAmmo] * attributeMultiplierMap[Attribute::MaxAmmo];

	// Show UI
	reloadBar->Enable();
	reloadFrame->Enable();

}

void Firearm::Update() {

	if (isReloading && Game::Time() >= reloadStartTick + baseAttributeMap[Attribute::ReloadTime] * attributeMultiplierMap[Attribute::ReloadTime]) {

		isReloading = false;

		// Hide UI
		reloadBar->Disable();
		reloadFrame->Disable();

	} else if(isReloading)
		reloadBar->GetComponent<Image>()->fillAmount = GetReloadingProgress();

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

float Firearm::GetAttribute(Attribute attribute) {

	return baseAttributeMap[attribute] * attributeMultiplierMap[attribute];

}