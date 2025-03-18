/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <GameCore.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const std::unordered_map<ItemIndex, std::unordered_map<FirearmAttributeIndex, float>> Firearm::BASE_ATTRIBUTE_MAP = {
	{ ItemIndex::Pistol, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 6.8f },
		{ FirearmAttributeIndex::Firerate, 356.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 20 },
		{ FirearmAttributeIndex::ReloadTime, 2.4f },
		}
	},
	{ ItemIndex::Shotgun, {
		{ FirearmAttributeIndex::CriticalChance, 0.3f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 4.7f },
		{ FirearmAttributeIndex::Firerate, 472.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 8 },
		{ FirearmAttributeIndex::ReloadTime, 3.6f },
		}
	},
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Firearm::Firearm() {

	lastReloadTick = 0.0f;
	isReloading = false;

	reloadTime = 0.0f;
	attributeMultiplierMap = {
		{ FirearmAttributeIndex::CriticalChance, 1.0f },
		{ FirearmAttributeIndex::CriticalDamageMultiplier, 1.0f },
		{ FirearmAttributeIndex::Damage, 1.0f },
		{ FirearmAttributeIndex::Firerate, 1.0f },
		{ FirearmAttributeIndex::MagazineCapacity, 1.0f },
		{ FirearmAttributeIndex::ReloadTime , 1.0f },
	};

	damage = 0.0f;
	fireRate = 0.0f;
	currentAmmo = 0;
	reserveAmmo = 0;
	magazineCapacity = 0;

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