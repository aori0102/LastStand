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

const std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, float>> Firearm::BASE_ATTRIBUTE_MAP = {
	{ ItemIndex::Pistol_M1911, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamage, 1.0f },
		{ FirearmAttributeIndex::Damage, 6.8f },
		{ FirearmAttributeIndex::Firerate, 356.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 20 },
		{ FirearmAttributeIndex::ReloadTime, 2.4f },
		}
	},
	{ ItemIndex::Shotgun_Beretta1301, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamage, 1.0f },
		{ FirearmAttributeIndex::Damage, 4.7f },
		{ FirearmAttributeIndex::Firerate, 129.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 8 },
		{ FirearmAttributeIndex::ReloadTime, 0.4f },
		}
	},
};
const std::unordered_map<ItemIndex, MediaObject> Firearm::FIREARM_ICON_INDEX_MAP = {
	{ ItemIndex::Pistol_M1911, MediaObject::Gun_M1911 },
	{ ItemIndex::Shotgun_Beretta1301, MediaObject::Gun_Beretta1301 },
};
const std::unordered_map<ItemIndex, std::string> Firearm::FIREARM_NAME_MAP = {
	{ ItemIndex::Pistol_M1911, "M1911" },
	{ ItemIndex::Shotgun_Beretta1301, "Beretta 1301" },
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Firearm::HandleReloading() {

	if (isReloading && GameCore::Time() >= lastReloadTick + attributeMap.at(FirearmAttributeIndex::ReloadTime)) {

		int magazineCapacity = static_cast<int>(attributeMap.at(FirearmAttributeIndex::MagazineCapacity));

		// Finish reloading
		if (reloadType == ReloadType::PerAmmo) {

			currentAmmo++;
			reserveAmmo--;

			if (currentAmmo == magazineCapacity || stopReload) {

				isReloading = false;
				stopReload = false;

			} else
				lastReloadTick = GameCore::Time();

		} else {

			isReloading = false;
			stopReload = false;

			if (reserveAmmo < magazineCapacity - currentAmmo) {

				currentAmmo += reserveAmmo;
				reserveAmmo = 0;

			} else {

				reserveAmmo -= magazineCapacity - currentAmmo;
				currentAmmo = magazineCapacity;

			}

		}

		currentAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
		reserveAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(reserveAmmo), Color::WHITE, RESERVE_AMMO_LABEL_SIZE);
		reserveAmmoLabel->transform->position = Vector2(
			(currentAmmoLabel->transform->position + (currentAmmoLabel->transform->scale + reserveAmmoLabel->transform->scale) / 2.0f).x + RESERVE_AMMO_LABEL_OFFSET,
			(currentAmmoLabel->transform->position - (currentAmmoLabel->transform->scale - reserveAmmoLabel->transform->scale) / 2.0f).y
		);

	}

}

bool Firearm::TryShoot() {

	if (isReloading) {

		stopReload = true;
		return false;

	}

	if (currentAmmo > 0 && GameCore::Time() >= lastShootTick + 60.0f / attributeMap.at(FirearmAttributeIndex::Firerate)) {

		lastShootTick = GameCore::Time();
		currentAmmo--;
		currentAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
		return true;

	}

	return false;

}

bool Firearm::IsCrit() {

	float chance = Random::Float(0.0f, 1.0f);
	return 0.0f <= chance && chance <= attributeMap.at(FirearmAttributeIndex::CriticalChance);

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

Firearm::Firearm(ItemIndex initItemIndex) : Item(initItemIndex) {

	if (BASE_ATTRIBUTE_MAP.find(GetIndex()) == BASE_ATTRIBUTE_MAP.end())
		throw std::exception("Firearm: FIrearm data does not exist");

	lastReloadTick = 0.0f;
	lastShootTick = 0.0f;
	isReloading = false;
	stopReload = false;
	firearmName = FIREARM_NAME_MAP.at(GetIndex());

	switch (GetIndex()) {

	case ItemIndex::Shotgun_Beretta1301:
		reloadType = ReloadType::PerAmmo;
		break;

	default:
		reloadType = ReloadType::Magazine;

	}

	attributeMultiplierMap = {
		{ FirearmAttributeIndex::CriticalChance, 1.0f },
		{ FirearmAttributeIndex::CriticalDamage, 1.0f },
		{ FirearmAttributeIndex::Damage, 1.0f },
		{ FirearmAttributeIndex::Firerate, 1.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 1.0f },
		{ FirearmAttributeIndex::ReloadTime , 1.0f },
	};
	attributeMap = BASE_ATTRIBUTE_MAP.at(GetIndex());

	currentAmmo = 0;
	reserveAmmo = 120;

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

	reloadLabel = new GameObject("", Layer::GUI);
	Text* reloadLabel_text = reloadLabel->AddComponent<Text>();
	reloadLabel_text->showOnScreen = true;
	reloadLabel_text->LoadText("Reloading...", Color::WHITE, 24);
	reloadLabel->transform->position = Vector2::down * 100.0f;
	reloadLabel->Render = [this, reloadLabel_text]() {
		if (isReloading)
			reloadLabel_text->Render();
		};

}

void Firearm::Update() {

	HandleReloading();

}

void Firearm::ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount) {

	attributeMultiplierMap.at(attributeIndex) = amount;
	attributeMap.at(attributeIndex) = BASE_ATTRIBUTE_MAP.at(GetIndex()).at(attributeIndex) * amount;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	if (reserveAmmo == 0 || currentAmmo == static_cast<int>(attributeMap.at(FirearmAttributeIndex::MagazineCapacity)))
		return;

	isReloading = true;
	lastReloadTick = GameCore::Time();

}

void Firearm::Equip() {

	ShowUI();

}

void Firearm::Dequip() {

	HideUI();

}

float Firearm::GetAttribute(FirearmAttributeIndex attributeIndex) {

	return attributeMap.at(attributeIndex);

}

std::string Firearm::GetName() const { return firearmName; }

Sprite* Firearm::GetIconSprite() const { return MediaManager::Instance()->GetObjectSprite(FIREARM_ICON_INDEX_MAP.at(GetIndex())); }