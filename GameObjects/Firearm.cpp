/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <GameCore.h>
#include <MediaManager.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int Firearm::CURRENT_AMMO_LABEL_SIZE = 32;
const int Firearm::RESERVE_AMMO_LABEL_SIZE = 10;
const float Firearm::RESERVE_AMMO_LABEL_OFFSET = 0.0f;
const Vector2 Firearm::AMMO_FRAME_POSTIION = Vector2(1119.0f, 660.0f);
const Vector2 Firearm::AMMO_ICON_POSTIION = Vector2(1130.0f, 676.0f);

const std::unordered_map<FirearmID, std::unordered_map<FirearmAttributeIndex, float>> Firearm::BASE_ATTRIBUTE_MAP = {
	{ FirearmID::M1911, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 6.8f },
		{ FirearmAttributeIndex::Firerate, 356.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 20 },
		{ FirearmAttributeIndex::ReloadTime, 2.4f },
		}
	},
	{ FirearmID::Beretta1301, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 4.7f },
		{ FirearmAttributeIndex::Firerate, 129.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 8 },
		{ FirearmAttributeIndex::ReloadTime, 3.6f },
		}
	},
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

bool Firearm::TryShoot() {

	if (isReloading)
		return false;

	if (currentAmmo > 0 && GameCore::Time() >= lastShootTick + 60.0f / fireRate) {

		lastShootTick = GameCore::Time();
		currentAmmo--;
		currentAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
		return true;

	}

	return false;

}

void Firearm::ShowUI() {

	ammoFrame->Enable();
	ammoIcon->Enable();
	currentAmmoLabel->Enable();
	reserveAmmoLabel->Enable();

}

void Firearm::HideUI() {

	ammoFrame->Disable();
	ammoIcon->Disable();
	currentAmmoLabel->Disable();
	reserveAmmoLabel->Disable();

}

Firearm::Firearm(FirearmID initFirearmID) {

	lastReloadTick = 0.0f;
	lastShootTick = 0.0f;
	isReloading = false;

	firearmID = initFirearmID;

	std::unordered_map<FirearmAttributeIndex, float> attributeMap = BASE_ATTRIBUTE_MAP.at(firearmID);

	reloadTime = attributeMap.at(FirearmAttributeIndex::ReloadTime);
	attributeMultiplierMap = {
		{ FirearmAttributeIndex::CriticalChance, 1.0f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 1.0f },
		{ FirearmAttributeIndex::Firerate, 1.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 1.0f },
		{ FirearmAttributeIndex::ReloadTime , 1.0f },
	};

	damage = attributeMap.at(FirearmAttributeIndex::ReloadTime);
	fireRate = attributeMap.at(FirearmAttributeIndex::Firerate);
	currentAmmo = 0;
	reserveAmmo = 120;
	magazineCapacity = attributeMap.at(FirearmAttributeIndex::MagazineCapacity);

	ammoFrame = new GameObject("Ammo Frame", Layer::GUI);
	Image* ammoFrame_image = ammoFrame->AddComponent<Image>();
	ammoFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoFrame), true);
	ammoFrame_image->showOnScreen = true;
	ammoFrame->transform->position = Math::SDLToC00(AMMO_FRAME_POSTIION, ammoFrame->transform->scale);
	ammoFrame->Render = [ammoFrame_image]() {
		ammoFrame_image->Render();
		};

	ammoIcon = new GameObject("Ammo Icon", Layer::GUI);
	Image* ammoIcon_image = ammoIcon->AddComponent<Image>();
	ammoIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoIcon), true);
	ammoIcon_image->showOnScreen = true;
	ammoIcon->transform->position = Math::SDLToC00(AMMO_ICON_POSTIION, ammoIcon->transform->scale);
	ammoIcon->Render = [ammoIcon_image]() {
		ammoIcon_image->Render();
		};

	currentAmmoLabel = new GameObject("Current Ammo Label", Layer::GUI);
	Text* currentAmmoLabel_text = currentAmmoLabel->AddComponent<Text>();
	currentAmmoLabel_text->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
	currentAmmoLabel_text->showOnScreen = true;
	currentAmmoLabel->transform->position = ammoFrame->transform->position;
	currentAmmoLabel->Render = [currentAmmoLabel_text]() {
		currentAmmoLabel_text->Render();
		};

	reserveAmmoLabel = new GameObject("Reserve Ammo Label", Layer::GUI);
	Text* reserveAmmoLabel_text = reserveAmmoLabel->AddComponent<Text>();
	reserveAmmoLabel_text->showOnScreen = true;
	reserveAmmoLabel_text->LoadText(std::to_string(reserveAmmo), Color::WHITE, RESERVE_AMMO_LABEL_SIZE);
	reserveAmmoLabel->transform->position = Vector2(
		(currentAmmoLabel->transform->position + (currentAmmoLabel->transform->scale + reserveAmmoLabel->transform->scale) / 2.0f).x + RESERVE_AMMO_LABEL_OFFSET,
		(currentAmmoLabel->transform->position - (currentAmmoLabel->transform->scale - reserveAmmoLabel->transform->scale) / 2.0f).y
	);
	reserveAmmoLabel->Render = [reserveAmmoLabel_text]() {
		reserveAmmoLabel_text->Render();
		};

	HideUI();

}

void Firearm::Update() {

	if (isReloading && GameCore::Time() >= lastReloadTick + reloadTime) {

		isReloading = false;

		if (reserveAmmo < magazineCapacity - currentAmmo) {

			currentAmmo += reserveAmmo;
			reserveAmmo = 0;

		} else {

			reserveAmmo -= magazineCapacity - currentAmmo;
			currentAmmo = magazineCapacity;

		}

		currentAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
		reserveAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(reserveAmmo), Color::WHITE, RESERVE_AMMO_LABEL_SIZE);
		reserveAmmoLabel->transform->position = Vector2(
			(currentAmmoLabel->transform->position + (currentAmmoLabel->transform->scale + reserveAmmoLabel->transform->scale) / 2.0f).x + RESERVE_AMMO_LABEL_OFFSET,
			(currentAmmoLabel->transform->position - (currentAmmoLabel->transform->scale - reserveAmmoLabel->transform->scale) / 2.0f).y
		);

	}

}

void Firearm::ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount) {

	attributeMultiplierMap.at(attributeIndex) = amount;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	if (reserveAmmo == 0 || currentAmmo == magazineCapacity)
		return;

	isReloading = true;
	lastReloadTick = GameCore::Time();

}