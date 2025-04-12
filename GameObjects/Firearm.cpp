/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Firearm.h>

#include <Ammunition.h>
#include <DataManager.h>
#include <GameCore.h>
#include <Inventory.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Texture.h>
#include <Transform.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int Firearm::CURRENT_AMMO_LABEL_SIZE = 32;
const int Firearm::RESERVE_AMMO_LABEL_SIZE = 14;
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
			{ FirearmAttributeIndex::Firerate, 316.9f },
			{ FirearmAttributeIndex::MagazineCapacity, 20 },
			{ FirearmAttributeIndex::ReloadTime, 2.4f },
		},
		.ammunitionItemIndex = ItemIndex::Ammo_9mm,
		.reloadType = ReloadType::Magazine,
	} },
	{ ItemIndex::Shotgun_Beretta1301, FirearmInfo {
		.name = "Beretta 1301 Tactical",
		.attributeMap = {
			{ FirearmAttributeIndex::CriticalChance, 0.3f },
			{ FirearmAttributeIndex::CriticalDamage, 1.0f },
			{ FirearmAttributeIndex::Damage, 4.1f },
			{ FirearmAttributeIndex::Firerate, 192.6f },
			{ FirearmAttributeIndex::MagazineCapacity, 8 },
			{ FirearmAttributeIndex::ReloadTime, 0.4f },
		},
		.ammunitionItemIndex = ItemIndex::Ammo_Slug,
		.reloadType = ReloadType::PerAmmo,
	} },
	{ ItemIndex::Rifle_M4, FirearmInfo {
		.name = "M4",
		.attributeMap = {
			{ FirearmAttributeIndex::CriticalChance, 0.3f },
			{ FirearmAttributeIndex::CriticalDamage, 1.0f },
			{ FirearmAttributeIndex::Damage, 14.8f },
			{ FirearmAttributeIndex::Firerate, 614.2f },
			{ FirearmAttributeIndex::MagazineCapacity, 42 },
			{ FirearmAttributeIndex::ReloadTime, 4.3f },
		},
		.ammunitionItemIndex = ItemIndex::Ammo_556,
		.reloadType = ReloadType::Magazine,
	} },
};

std::unordered_map<ItemIndex, FirearmInfo> Firearm::firearmInfoMap = Firearm::BASE_FIREARM_INFO_MAP;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

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

void Firearm::OnShoot() {

	lastShootTick = GameCore::Time();

}

void Firearm::HandleReloading() {

	if (isReloading && GameCore::Time() >= lastReloadTick + firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::ReloadTime)) {

		int magazineCapacity = static_cast<int>(firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::MagazineCapacity));

		// Finish reloading
		if (reloadType == ReloadType::PerAmmo) {

			if (!Player::Instance()->TryConsumeAmmo(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex)) {

				isReloading = false;
				stopReload = false;
				return;

			}

			TryAddToStack();

			if (currentStack == magazineCapacity || stopReload) {

				isReloading = false;
				stopReload = false;

			} else
				lastReloadTick = GameCore::Time();

		} else {

			isReloading = false;
			stopReload = false;

			int reserveAmmo = Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex);
			int toReload = std::min(reserveAmmo, magazineCapacity - currentStack);

			if (!Player::Instance()->TryConsumeAmmo(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex, toReload))
				throw std::exception("Reload failure! Not enough ammo. Unexpected case");

			TryAddToStack(toReload);

		}

		UpdateReserveLabel();

	}

}

bool Firearm::CanShoot() {

	if (isReloading) {

		stopReload = true;
		return false;

	}

	return currentStack > 0 && GameCore::Time() >= lastShootTick + 60.0f / firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::Firerate);

}

bool Firearm::IsCrit() {

	float chance = Random::Float(0.0f, 1.0f);
	return 0.0f <= chance && chance <= firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::CriticalChance);

}

Firearm::Firearm() {

	lastReloadTick = 0.0f;
	lastShootTick = 0.0f;
	isReloading = false;
	stopReload = false;
	previousCurrentAmmo = currentStack;

	reloadType = ReloadType::Magazine;

	ammoFrame = GameObject::Instantiate("Ammo Frame", Layer::GUI);
	Image* ammoFrame_image = ammoFrame->AddComponent<Image>();
	ammoFrame_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoFrame), true);
	ammoFrame_image->showOnScreen = true;
	ammoFrame->transform->position = Math::SDLToC00(AMMO_FRAME_POSTIION, ammoFrame->transform->scale);
	ammoFrame->Render = [ammoFrame_image]() {
		ammoFrame_image->Render();
		};

	ammoIcon = GameObject::Instantiate("Ammo Icon", Layer::GUI);
	Image* ammoIcon_image = ammoIcon->AddComponent<Image>();
	ammoIcon_image->LinkSprite(MediaManager::Instance()->GetUISprite(MediaUI::Firearm_AmmoIcon), true);
	ammoIcon_image->showOnScreen = true;
	ammoIcon->transform->position = Math::SDLToC00(AMMO_ICON_POSTIION, ammoIcon->transform->scale);
	ammoIcon->Render = [ammoIcon_image]() {
		ammoIcon_image->Render();
		};

	currentAmmoLabel = GameObject::Instantiate("Current Ammo Label", Layer::GUI);
	Text* currentAmmoLabel_text = currentAmmoLabel->AddComponent<Text>();
	currentAmmoLabel_text->showOnScreen = true;
	currentAmmoLabel_text->LoadText(std::to_string(currentStack), Color::WHITE, CURRENT_AMMO_LABEL_SIZE);
	UpdateCurrentLabel();
	currentAmmoLabel->transform->position = ammoFrame->transform->position;
	currentAmmoLabel->Render = [currentAmmoLabel_text]() {
		currentAmmoLabel_text->Render();
		};

	reserveAmmoLabel = GameObject::Instantiate("Reserve Ammo Label", Layer::GUI);
	Text* reserveAmmoLabel_text = reserveAmmoLabel->AddComponent<Text>();
	reserveAmmoLabel_text->showOnScreen = true;
	UpdateReserveLabel();
	reserveAmmoLabel->Render = [reserveAmmoLabel_text]() {
		reserveAmmoLabel_text->Render();
		};

	HideUI();

	reloadLabel = GameObject::Instantiate("Reload Label", Layer::GUI);
	Text* reloadLabel_text = reloadLabel->AddComponent<Text>();
	reloadLabel_text->showOnScreen = true;
	reloadLabel_text->LoadText("Reloading...", Color::WHITE, 24);
	reloadLabel->transform->position = Vector2::down * 100.0f;
	reloadLabel->Render = [this, reloadLabel_text]() {
		if (isReloading)
			reloadLabel_text->Render();
		};

}

Firearm::~Firearm() {

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

	firearmInfoMap.at(GetIndex()).attributeMap.clear();

}

void Firearm::Reload() {

	if (isReloading)
		return;

	if (Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex) == 0 || currentStack == static_cast<int>(firearmInfoMap.at(GetIndex()).attributeMap.at(FirearmAttributeIndex::MagazineCapacity)))
		return;

	isReloading = true;
	lastReloadTick = GameCore::Time();

}

void Firearm::UpdateReserveLabel() {

	if (GetIndex() == ItemIndex::None)
		// The index is not yet updated
		return;

	reserveAmmoLabel->GetComponent<Text>()->LoadText(
		std::to_string(Player::Instance()->GetAmmoCount(BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex)),
		Color::WHITE,
		RESERVE_AMMO_LABEL_SIZE
	);
	Align::Right(reserveAmmoLabel->transform, currentAmmoLabel->transform);
	Align::Bottom(reserveAmmoLabel->transform, currentAmmoLabel->transform);
	reserveAmmoLabel->transform->position += Vector2::right *
		(reserveAmmoLabel->transform->scale.x + RESERVE_AMMO_LABEL_OFFSET);

}

void Firearm::UpdateCurrentLabel() {

	currentAmmoLabel->GetComponent<Text>()->LoadText(
		std::to_string(currentStack),
		Color::WHITE,
		CURRENT_AMMO_LABEL_SIZE
	);

}

void Firearm::Equip() {

	UpdateReserveLabel();

	ShowUI();

}

void Firearm::Dequip() {

	isReloading = false;

	HideUI();

}

void Firearm::Update() {

	if (currentStack != previousCurrentAmmo) {

		previousCurrentAmmo = currentStack;
		UpdateCurrentLabel();

	}

	HandleReloading();

}

bool Firearm::TryAddToStack(int amount) {

	currentStack += amount;
	return true;

}

bool Firearm::TryRemoveFromStack(int amount) {

	if (currentStack < amount)
		return false;

	currentStack -= amount;
	return true;

}

bool Firearm::ItemRanOut() { return false; }

float Firearm::GetAttribute(FirearmAttributeIndex attributeIndex) {

	return firearmInfoMap.at(GetIndex()).attributeMap.at(attributeIndex);

}

ItemIndex Firearm::GetAmmoItemIndex() { return BASE_FIREARM_INFO_MAP.at(GetIndex()).ammunitionItemIndex; }

std::string Firearm::GetName() const { return firearmName; }

void Firearm::ModifyAttributeMultiplier(ItemIndex firearmIndex, FirearmAttributeIndex attributeIndex, float amount) {

	firearmInfoMap.at(firearmIndex).attributeMap.at(attributeIndex)
		= BASE_FIREARM_INFO_MAP.at(firearmIndex).attributeMap.at(attributeIndex) * amount;

}