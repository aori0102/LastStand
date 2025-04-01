/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <Ammunition.h>
#include <GameCore.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int Firearm::CURRENT_AMMO_LABEL_SIZE = 32;
const int Firearm::RESERVE_AMMO_LABEL_SIZE = 10;
const float Firearm::RESERVE_AMMO_LABEL_OFFSET = 0.0f;
const Vector2 Firearm::AMMO_FRAME_POSTIION = Vector2(1119.0f, 660.0f);
const Vector2 Firearm::AMMO_ICON_POSTIION = Vector2(1130.0f, 676.0f);

const std::unordered_map<ItemIndex, FirearmInfo> Firearm::BASE_FIREARM_INFO_MAP = {
	{ ItemIndex::Pistol_M1911, FirearmInfo {
		.name = "M1911",
		.attributeMap = {
			{ FirearmAttributeIndex::CriticalChance, 0.3f },
			{ FirearmAttributeIndex::CriticalDamage, 1.0f },
			{ FirearmAttributeIndex::Damage, 6.8f },
			{ FirearmAttributeIndex::Firerate, 356.0f },
			{ FirearmAttributeIndex::MagazineCapacity, 20 },
			{ FirearmAttributeIndex::ReloadTime, 2.4f },
		},
		.ammunitionID = AmmunitionID::Nine_Mil,
		.iconIndex = MediaObject::Gun_M1911,
		.reloadType = ReloadType::Magazine,
	} },
	{ ItemIndex::Shotgun_Beretta1301, FirearmInfo {
		.name = "Beretta 1301 Tactical",
		.attributeMap = {
			{ FirearmAttributeIndex::CriticalChance, 0.3f },
			{ FirearmAttributeIndex::CriticalDamage, 1.0f },
			{ FirearmAttributeIndex::Damage, 4.1f },
			{ FirearmAttributeIndex::Firerate, 192.0f },
			{ FirearmAttributeIndex::MagazineCapacity, 8 },
			{ FirearmAttributeIndex::ReloadTime, 0.4f },
		},
		.ammunitionID = AmmunitionID::Slug,
		.iconIndex = MediaObject::Gun_Beretta1301,
		.reloadType = ReloadType::PerAmmo,
	} },

};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Firearm::HandleReloading() {

	if (isReloading && GameCore::Time() >= lastReloadTick + attributeMap.at(FirearmAttributeIndex::ReloadTime)) {

		int magazineCapacity = static_cast<int>(attributeMap.at(FirearmAttributeIndex::MagazineCapacity));

		// Finish reloading
		if (reloadType == ReloadType::PerAmmo) {

			if (!Player::Instance()->TryConsumeAmmo(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionID)) {

				isReloading = false;
				stopReload = false;
				return;

			}

			currentAmmo++;

			if (currentAmmo == magazineCapacity || stopReload) {

				isReloading = false;
				stopReload = false;

			} else
				lastReloadTick = GameCore::Time();

		} else {

			isReloading = false;
			stopReload = false;

			int reserveAmmo = Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionID);
			int toReload = std::min(reserveAmmo, magazineCapacity - currentAmmo);

			if (!Player::Instance()->TryConsumeAmmo(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionID, toReload))
				throw std::exception("Reload failure! Not enough ammo. Unexpected case");

			currentAmmo += toReload;

		}

		currentAmmoLabel->GetComponent<Text>()->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
		UpdateReserveLabel();

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

	auto it_baseFirearmInfo = BASE_FIREARM_INFO_MAP.find(initItemIndex);
	if (it_baseFirearmInfo == BASE_FIREARM_INFO_MAP.end())
		throw std::exception("Firearm: FIrearm data does not exist");

	lastReloadTick = 0.0f;
	lastShootTick = 0.0f;
	isReloading = false;
	stopReload = false;

	reloadType = (it_baseFirearmInfo->second).reloadType;
	attributeMap = (it_baseFirearmInfo->second).attributeMap;

	currentAmmo = 0;

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
	currentAmmoLabel_text->showOnScreen = true;
	currentAmmoLabel_text->LoadText(std::to_string(currentAmmo), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
	currentAmmoLabel->transform->position = ammoFrame->transform->position;
	currentAmmoLabel->Render = [currentAmmoLabel_text]() {
		currentAmmoLabel_text->Render();
		};

	reserveAmmoLabel = new GameObject("Reserve Ammo Label", Layer::GUI);
	Text* reserveAmmoLabel_text = reserveAmmoLabel->AddComponent<Text>();
	reserveAmmoLabel_text->showOnScreen = true;
	UpdateReserveLabel();
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

void Firearm::ModifyAttributeMultiplier(FirearmAttributeIndex attributeIndex, float amount) {

	attributeMap.at(attributeIndex) = BASE_FIREARM_INFO_MAP.at(GetIndex()).attributeMap.at(attributeIndex) * amount;

}

void Firearm::Reload() {

	if (isReloading)
		return;

	if (Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionID) == 0 || currentAmmo == static_cast<int>(attributeMap.at(FirearmAttributeIndex::MagazineCapacity)))
		return;

	isReloading = true;
	lastReloadTick = GameCore::Time();

}

void Firearm::UpdateReserveLabel() {

	reserveAmmoLabel->GetComponent<Text>()->LoadText(
		std::to_string(Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionID)),
		Color::WHITE,
		RESERVE_AMMO_LABEL_SIZE
	);
	Align::Right(reserveAmmoLabel->transform, currentAmmoLabel->transform);
	Align::Bottom(reserveAmmoLabel->transform, currentAmmoLabel->transform);
	reserveAmmoLabel->transform->position += Vector2::right *
		(reserveAmmoLabel->transform->scale.x + RESERVE_AMMO_LABEL_OFFSET);

}

void Firearm::Equip() {

	UpdateReserveLabel();

	ShowUI();

}

void Firearm::Dequip() {

	HideUI();

}

void Firearm::Update() {

	HandleReloading();

}

void Firearm::OnDestroy() {

	GameObject::Destroy(ammoIcon);
	ammoIcon = nullptr;

	GameObject::Destroy(ammoFrame);
	ammoFrame = nullptr;

	GameObject::Destroy(currentAmmoLabel);
	currentAmmoLabel = nullptr;

	GameObject::Destroy(reserveAmmoLabel);
	reserveAmmoLabel = nullptr;

	GameObject::Destroy(reloadLabel);
	reloadLabel = nullptr;

	attributeMap.clear();

}

bool Firearm::TryAddToStack(int amount) { return false; }

bool Firearm::TryRemoveFromStack(int amount) { return false; }

float Firearm::GetAttribute(FirearmAttributeIndex attributeIndex) {

	return attributeMap.at(attributeIndex);

}

std::string Firearm::GetName() const { return firearmName; }