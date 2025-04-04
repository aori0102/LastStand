/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Player.h>

#include <functional>

#include <Ammunition.h>
#include <AnimationManager.h>
#include <Animation.h>
#include <Bullet.h>
#include <Firearm.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <GameManager.h>
#include <Item.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <Texture.h>
#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float Player::MOVING_AIM_DEVIATION = 27.0f;
const float Player::STANDING_AIM_DEVIATION = 10.0f;
const float Player::ADS_AIM_DEVIATION = 5.0f;
const float Player::MOVEMENT_SPEED_CHANGE_RATE = 50.0f;
const float Player::CAMERA_AIM_ZOOM = 1.3f;
const float Player::DEFAULT_MOVEMENT_SPEED = 500.0f;
const float Player::AIM_MOVEMENT_SPEED = 300.0f;
const float Player::SPRINT_MOVEMENT_SPEED = 750.0f;
const float Player::STAMINA_DRAIN_RATE = 29.0f;
const float Player::STAMINA_RECOVERY_RATE = 9.0f;
Player* Player::instance = nullptr;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Player::HandleActions() {

	if (GameCore::SelectedUI())
		return;

	// Aiming
	if (GameCore::GetMouseState(MouseButton::Right).started) {

		GameCore::SetCameraZoom(CAMERA_AIM_ZOOM);
		isAiming = true;

	} else if (GameCore::GetMouseState(MouseButton::Right).canceled) {

		GameCore::SetCameraZoom(1.0f);
		isAiming = false;

	}
	// Hotbar
	Inventory* inventory = GetComponent<Inventory>();
	if (GameCore::GetKeyState(SDLK_1).started)
		inventory->SelectSlot(HotBarSlotIndex::First);
	else if (GameCore::GetKeyState(SDLK_2).started)
		inventory->SelectSlot(HotBarSlotIndex::Second);
	else if (GameCore::GetKeyState(SDLK_3).started)
		inventory->SelectSlot(HotBarSlotIndex::Third);
	else if (GameCore::GetKeyState(SDLK_4).started)
		inventory->SelectSlot(HotBarSlotIndex::Forth);
	else if (GameCore::GetKeyState(SDLK_5).started)
		inventory->SelectSlot(HotBarSlotIndex::Fifth);

	itemIndex = inventory->GetCurrentItemIndex();

	// Use item
	if (itemIndex == ItemIndex::Rifle_M4)
		usingItem = GameCore::GetMouseState(MouseButton::Left).performed;
	else
		usingItem = GameCore::GetMouseState(MouseButton::Left).started;

	usingItem = usingItem && inventory->TryUseCurrent();

	// Toggle inventory UI
	if (GameCore::GetKeyState(SDLK_i).started)
		inventory->ToggleInventory();

	// Reload firearm
	if (GameCore::GetKeyState(SDLK_r).started) {

		Item* currentItem = inventory->GetCurrentItem();
		Firearm* currentFirearm = nullptr;
		if (currentItem)
			currentFirearm = dynamic_cast<Firearm*>(currentItem);

		if (currentFirearm)
			currentFirearm->Reload();

	}

	// Sprint
	if (GameCore::GetKeyState(SDLK_LSHIFT).started)
		isSprinting = true;
	else if (GameCore::GetKeyState(SDLK_LSHIFT).canceled)
		isSprinting = false;

}

void Player::HandleMovement() {

	if (isAiming)
		targetMovementSpeed = AIM_MOVEMENT_SPEED;
	else if (isSprinting && GetComponent<Humanoid>()->GetStamina() > 0)
		targetMovementSpeed = SPRINT_MOVEMENT_SPEED;
	else
		targetMovementSpeed = DEFAULT_MOVEMENT_SPEED;

	currentMovementSpeed = Math::Lerp(currentMovementSpeed, targetMovementSpeed, GameCore::DeltaTime() * MOVEMENT_SPEED_CHANGE_RATE);

	// Input
	Vector2 input(0.0f, 0.0f);

	if (GameCore::GetKeyState(SDLK_w).performed)
		input += Vector2::up;

	if (GameCore::GetKeyState(SDLK_a).performed)
		input += Vector2::left;

	if (GameCore::GetKeyState(SDLK_s).performed)
		input += Vector2::down;

	if (GameCore::GetKeyState(SDLK_d).performed)
		input += Vector2::right;

	isMoving = (input != Vector2::zero);

	// Apply movement
	transform->Translate(input.Normalize() * currentMovementSpeed * GameCore::DeltaTime());

	// Assign deviation
	if (isMoving)
		aimDeviation = MOVING_AIM_DEVIATION;
	else
		aimDeviation = STANDING_AIM_DEVIATION;

	if (isAiming)
		aimDeviation = ADS_AIM_DEVIATION;

}

void Player::HandleFacing() {

	// Calculate rotation
	forward = (GameCore::ScreenToWorldPosition(GameCore::GetMouseInput()) - transform->position).Normalize();

}

void Player::HandleStamina() {

	Humanoid* humanoid = GetComponent<Humanoid>();

	if (isSprinting)
		humanoid->DrainStamina(STAMINA_DRAIN_RATE * GameCore::DeltaTime());
	else
		humanoid->GainStamina(STAMINA_RECOVERY_RATE * GameCore::DeltaTime());

}

void Player::InitializeAnimation() {

	AnimationController* animController = AddComponent<AnimationController>();

	animController->AddAnimationClip(AnimationIndex::Player_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Pistol_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Pistol_Shoot);
	animController->AddAnimationClip(AnimationIndex::Player_Shotgun_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Shotgun_Shoot);
	animController->AddAnimationClip(AnimationIndex::Player_Rifle_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Rifle_Shoot);
	animController->AddAnimationClip(AnimationIndex::Player_MedKit);
	animController->AddAnimationClip(AnimationIndex::Player_Item_Transition, true);

	animController->MakeDefault(AnimationIndex::Player_Idle);

	// --- ITEM STATE MACHINE ---
	animController->AddTransition(
		AnimationIndex::Player_Idle,
		AnimationIndex::Player_Item_Transition,
		[this]() {
			return itemIndex != ItemIndex::None;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Item_Transition,
		AnimationIndex::Player_Pistol_Idle,
		[this]() {
			return itemIndex == ItemIndex::Pistol_M1911;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Item_Transition,
		AnimationIndex::Player_Shotgun_Idle,
		[this]() {
			return itemIndex == ItemIndex::Shotgun_Beretta1301;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Item_Transition,
		AnimationIndex::Player_Rifle_Idle,
		[this]() {
			return itemIndex == ItemIndex::Rifle_M4;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Item_Transition,
		AnimationIndex::Player_MedKit,
		[this]() {
			return itemIndex == ItemIndex::MedKit;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Idle,
		AnimationIndex::Player_Item_Transition,
		[this]() {
			return itemIndex != ItemIndex::Pistol_M1911;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Idle,
		AnimationIndex::Player_Item_Transition,
		[this]() {
			return itemIndex != ItemIndex::Shotgun_Beretta1301;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Rifle_Idle,
		AnimationIndex::Player_Item_Transition,
		[this]() {
			return itemIndex != ItemIndex::Rifle_M4;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_MedKit,
		AnimationIndex::Player_Item_Transition,
		[this]() {
			return itemIndex != ItemIndex::MedKit;
		}
	);

	// Items with no holding animation
	animController->AddTransition(
		AnimationIndex::Player_Item_Transition,
		AnimationIndex::Player_Idle,
		[this]() {
			switch (itemIndex) {
			case ItemIndex::Ammo_Slug:
			case ItemIndex::Ammo_9mm:
			case ItemIndex::Ammo_556:
			case ItemIndex::None:
				return true;
			}
			return false;
		}
	);

	// --- PISTOL ---
	animController->AddTransition(
		AnimationIndex::Player_Pistol_Idle,
		AnimationIndex::Player_Pistol_Shoot,
		[this]() {
			return usingItem;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Shoot,
		AnimationIndex::Player_Pistol_Idle
	);

	// --- SHOTGUN ---
	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Idle,
		AnimationIndex::Player_Shotgun_Shoot,
		[this]() {
			return usingItem;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Shoot,
		AnimationIndex::Player_Shotgun_Idle
	);

	// --- RIFLE ---
	animController->AddTransition(
		AnimationIndex::Player_Rifle_Idle,
		AnimationIndex::Player_Rifle_Shoot,
		[this]() {
			return usingItem;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Rifle_Shoot,
		AnimationIndex::Player_Rifle_Idle
	);

}

void Player::InitializeData() {

	// Components
	transform->scale = Vector2(50.0f, 50.0f);
	AddComponent<BoxCollider>();

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), false);
	playerSprite->showOnScreen = false;

	Inventory* inventory = AddComponent<Inventory>();
	inventory->AddItem(ItemIndex::Rifle_M4);
	inventory->AddItem(ItemIndex::Pistol_M1911);
	inventory->AddItem(ItemIndex::Shotgun_Beretta1301);
	inventory->AddItem(ItemIndex::MedKit);
	inventory->AddItem(ItemIndex::Ammo_Slug, 25);
	inventory->AddItem(ItemIndex::Ammo_9mm, 80);
	inventory->AddItem(ItemIndex::Ammo_556, 180);

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->mass = 60.0f;
	rigidBody->drag = 6.0f;

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(100.0f);
	humanoid->OnDeath = [this]() {
		GameManager::Instance()->ReportDead(this);
		};

	// Field

	isMoving = false;
	isAiming = false;
	isSprinting = false;
	usingItem = false;
	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());
	currentMovementSpeed = DEFAULT_MOVEMENT_SPEED;
	targetMovementSpeed = DEFAULT_MOVEMENT_SPEED;
	aimDeviation = STANDING_AIM_DEVIATION;
	playerAttributeMap = {
		{ PlayerAttribute::Accuracy, 0.3f },
		{ PlayerAttribute::ReloadSpeed, 1.0f },
		{ PlayerAttribute::MaxHealth, 100.0f },
	};
	itemIndex = ItemIndex::None;
	forward = Vector2::zero;

	usingItem = false;
	currentAnimationTime = 0.0f;
	currentAnimationStartTick = 0.0f;

	Render = [this]() { PlayerRender(); };

}

Player::Player() : GameObject("Player", Layer::Player) {

	std::cout << "Player created with address " << this << std::endl;

	if (instance)
		throw std::exception("This is a singleplayer game!");

	instance = this;

	InitializeData();

	InitializeAnimation();

}

Player::~Player() {

	playerAttributeMap.clear();

	instance = nullptr;

}

void Player::PlayerRender() {

	GetComponent<AnimationController>()->RenderCurrent(
		transform->position,
		transform->scale,
		Math::RadToDeg(forward.Angle())
	);

	GetComponent<BoxCollider>()->Debug();

}

void Player::GiveItem(ItemIndex itemIndex, int amount) {

	GetComponent<Inventory>()->AddItem(itemIndex, amount);

}

void Player::SetAttribute(PlayerAttribute playerAttribute, float value) {

	playerAttributeMap.at(playerAttribute) = value;

	switch (playerAttribute) {

	case PlayerAttribute::MaxHealth:

		GetComponent<Humanoid>()->SetHealth(value);

		break;

	case PlayerAttribute::ReloadSpeed: {

		std::vector<Firearm*> firearmList = GetFirearmList();
		for (Firearm* firearm : firearmList)
			firearm->ModifyAttributeMultiplier(
				FirearmAttributeIndex::ReloadTime, 1.0f / value
			);

		break;

	}

	case PlayerAttribute::Accuracy: {

		std::vector<Firearm*> firearmList = GetFirearmList();
		for (Firearm* firearm : firearmList)
			firearm->ModifyAttributeMultiplier(
				FirearmAttributeIndex::CriticalChance, value
			);

		break;

	}

	}

}

void Player::Update() {

	HandleMovement();
	HandleFacing();
	HandleActions();
	HandleStamina();

}

int Player::GetAmmoCount(AmmunitionID ammunitionID) {

	return GetComponent<Inventory>()->GetItemCount(Ammunition::AMMO_ITEM_INDEX_MAP.at(ammunitionID));

}

float Player::GetAttribute(PlayerAttribute playerAttribute) { return playerAttributeMap.at(playerAttribute); }

bool Player::TryConsumeAmmo(AmmunitionID ammunitionID, int amount) {

	return GetComponent<Inventory>()->TryRemoveItem(Ammunition::AMMO_ITEM_INDEX_MAP.at(ammunitionID), amount);

}

Vector2 Player::GetAimingDirection() {

	return forward.Rotate(Math::DegToRad(Random::Sign(Random::Float(0.0f, aimDeviation))));

}

std::vector<Firearm*> Player::GetFirearmList() {

	return GetComponent<Inventory>()->GetItemListOfType<Firearm>();

}

Player* Player::Instance() { return instance; }