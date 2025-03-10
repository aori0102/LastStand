#include <Firearm.h>
#include <Player.h>
#include <Projectile.h>
#include <GameCore.h>
#include <PlayerUI.h>
#include <Texture.h>
#include <string>
#include <MediaManager.h>

const float BULLET_VELOCITY = 7000.0f;

const std::unordered_map<Firearm::UIIndex, Vector2> Firearm::UI_POSITION_MAP = {
	{ Firearm::UIIndex::AmmoFrame, Vector2(1119.0f, 660.0f) },
	{ Firearm::UIIndex::AmmoLabel, Vector2(-20.0f, 0.0f) },
	{ Firearm::UIIndex::AmmoIcon, Vector2(1130.0f, 676.0f) }
};
const std::unordered_map<Firearm::UIIndex, int> Firearm::UI_FONT_SIZE_MAP = {
	{ Firearm::UIIndex::AmmoLabel, 20 }
};
const std::unordered_map<Firearm::UIIndex, std::string> Firearm::UI_LABEL_MAP = {
	{ Firearm::UIIndex::AmmoFrame, "AmmoFrame" },
	{ Firearm::UIIndex::AmmoIcon, "AmmoIcon" },
	{ Firearm::UIIndex::AmmoLabel, "AmmoLabel" }
};
const std::unordered_map<Firearm::UIIndex, std::string> Firearm::UI_TEXT_MAP = {
	{ Firearm::UIIndex::AmmoLabel, " / " }
};
const std::string Firearm::FOLDER_PATH = "./Asset/Firearm/";
const std::string Firearm::FILE_EXTENSION = ".png";

Firearm::Firearm(float initDamage, int initAmmoCapacity, float initFireRate, float initReloadTime) {

	// Base
	baseAttributeMap[Attribute::Damage] = initDamage;
	baseAttributeMap[Attribute::ReloadTime] = initReloadTime;
	baseAttributeMap[Attribute::MaxAmmo] = initAmmoCapacity;
	currentAmmo = initAmmoCapacity;
	fireRate = initFireRate;
	reserveAmmo = 120;

	previousCurrentAmmo = currentAmmo;
	previousReserveAmmo = reserveAmmo;

	// Multiplier
	attributeMultiplierMap[Attribute::Damage] = 1.0f;
	attributeMultiplierMap[Attribute::ReloadTime] = 1.0f;
	attributeMultiplierMap[Attribute::MaxAmmo] = 1.0f;

	shotDelay = 60.0f / fireRate;
	lastShotTick = 0.0f;
	isReloading = false;
	reloadStartTick = 0.0f;

	InitializeUI();

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
	if (GameCore::Time() < lastShotTick + shotDelay)
		return false;

	// Get the direction the player is facing
	Vector2 direction = player->GetAimingDirection();

	// Get player's position
	Vector2 origin = player->GetComponent<Transform>()->position;

	// Fire
	new Projectile(player, origin, direction, BULLET_VELOCITY, baseAttributeMap[Attribute::Damage] * attributeMultiplierMap[Attribute::Damage]);
	currentAmmo--;
	lastShotTick = GameCore::Time();

	return true;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	isReloading = true;
	reloadStartTick = GameCore::Time();
	currentAmmo = baseAttributeMap[Attribute::MaxAmmo] * attributeMultiplierMap[Attribute::MaxAmmo];

}

void Firearm::Update() {

	if (isReloading && GameCore::Time() >= reloadStartTick + baseAttributeMap[Attribute::ReloadTime] * attributeMultiplierMap[Attribute::ReloadTime])
		isReloading = false;

}

bool Firearm::IsReloading() const { return isReloading; }

int Firearm::CurrentAmmo() const {

	return currentAmmo;

}

void Firearm::ModifyAttributeMultiplier(Attribute attribute, float amount) {

	attributeMultiplierMap[attribute] = amount;

}

float Firearm::GetAttribute(Attribute attribute) {

	return baseAttributeMap[attribute] * attributeMultiplierMap[attribute];

}

void Firearm::InitializeUI() {

	// --- AMMO FRAME ---
	uiElementMap[UIIndex::AmmoFrame] = new GameObject(UI_LABEL_MAP.at(UIIndex::AmmoFrame), Layer::GUI);
	Image* ammoFrame_image = uiElementMap.at(UIIndex::AmmoFrame)->AddComponent<Image>();
	ammoFrame_image->showOnScreen = true;
	ammoFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoFrame));
	ammoFrame_image->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIIndex::AmmoFrame), ammoFrame_image->transform->scale);
	uiElementMap.at(UIIndex::AmmoFrame)->Render = [ammoFrame_image]() {
		ammoFrame_image->Render();
		};

	// --- AMMO ICON ---
	uiElementMap[UIIndex::AmmoIcon] = new GameObject(UI_LABEL_MAP.at(UIIndex::AmmoIcon), Layer::GUI);
	Image* ammoIcon_image = uiElementMap.at(UIIndex::AmmoIcon)->AddComponent<Image>();
	ammoIcon_image->showOnScreen = true;
	ammoIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoIcon));
	ammoIcon_image->transform->position = Math::SDLToC00(UI_POSITION_MAP.at(UIIndex::AmmoIcon), ammoIcon_image->transform->scale);
	uiElementMap.at(UIIndex::AmmoIcon)->Render = [ammoIcon_image]() {
		ammoIcon_image->Render();
		};

	// --- AMMO LABEL ---
	uiElementMap[UIIndex::AmmoLabel] = new GameObject(UI_LABEL_MAP.at(UIIndex::AmmoLabel), Layer::GUI);
	Text* ammoLabel_text = uiElementMap.at(UIIndex::AmmoLabel)->AddComponent<Text>();
	ammoLabel_text->showOnScreen = true;
	ammoLabel_text->LoadText(std::to_string(currentAmmo) + UI_TEXT_MAP.at(UIIndex::AmmoLabel) + std::to_string(reserveAmmo), Color::WHITE, UI_FONT_SIZE_MAP.at(UIIndex::AmmoLabel));
	ammoLabel_text->transform->position = Vector2(
		ammoFrame_image->transform->position.x + (ammoFrame_image->transform->scale.x - ammoLabel_text->transform->scale.x) / 2.0f + UI_POSITION_MAP.at(UIIndex::AmmoLabel).x,
		ammoFrame_image->transform->position.y
	);
	uiElementMap.at(UIIndex::AmmoLabel)->Render = [this, ammoLabel_text]() {
		if (currentAmmo != previousCurrentAmmo || reserveAmmo != previousReserveAmmo) {
			ammoLabel_text->LoadText(std::to_string(currentAmmo) + UI_TEXT_MAP.at(UIIndex::AmmoLabel) + std::to_string(reserveAmmo), Color::WHITE, UI_FONT_SIZE_MAP.at(UIIndex::AmmoLabel));
			previousCurrentAmmo = currentAmmo;
			previousReserveAmmo = reserveAmmo;
		}
		ammoLabel_text->Render();
		};

}

void Firearm::OnDestroy() {



}