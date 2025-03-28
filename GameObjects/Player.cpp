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
#include <Item.h>
#include <ItemManager.h>
#include <Firearm.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <Bullet.h>
#include <Texture.h>
#include <Type.h>

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
		inventory->SelectSlot(InventorySlotIndex::First);
	else if (GameCore::GetKeyState(SDLK_2).started)
		inventory->SelectSlot(InventorySlotIndex::Second);
	else if (GameCore::GetKeyState(SDLK_3).started)
		inventory->SelectSlot(InventorySlotIndex::Third);
	else if (GameCore::GetKeyState(SDLK_4).started)
		inventory->SelectSlot(InventorySlotIndex::Forth);
	else if (GameCore::GetKeyState(SDLK_5).started)
		inventory->SelectSlot(InventorySlotIndex::Fifth);

	itemIndex = inventory->GetCurrentItemIndex();

	// Use item
	usingItem = GameCore::GetMouseState(MouseButton::Left).started && inventory->TryUseCurrent();

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

void Player::InitializeData() {

	currentMovementSpeed = DEFAULT_MOVEMENT_SPEED;
	aimDeviation = STANDING_AIM_DEVIATION;

	itemIndex = ItemIndex::None;

	canInteract = true;
	usingItem = false;
	isMoving = false;
	isAiming = false;

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), false);
	playerSprite->showOnScreen = false;

	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());

	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	Inventory* inventory = AddComponent<Inventory>();
	inventory->AddItem(ItemIndex::Pistol_M1911);
	inventory->AddItem(ItemIndex::Shotgun_Beretta1301);
	inventory->AddItem(ItemIndex::MedKit);
	inventory->AddItem(ItemIndex::Ammo_Slug, 25);

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->mass = 60.0f;
	rigidBody->drag = 6.0f;

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(100.0f);
	humanoid->OnDeath = [this]() {
		GameManager::Instance()->ReportDead(this);
		};

	currentAnimationStartTick = 0.0f;
	currentAnimationTime = 0.0f;

	Render = [this]() { PlayerRender(); };

}

void Player::InitializeAnimation() {

	AnimationController* animController = AddComponent<AnimationController>();

	animController->AddAnimationClip(AnimationIndex::Player_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Pistol_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Pistol_Shoot);
	animController->AddAnimationClip(AnimationIndex::Player_Shotgun_Idle);
	animController->AddAnimationClip(AnimationIndex::Player_Shotgun_Shoot);
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

}

Player::Player() : GameObject("Player", Layer::Player) {

	if (instance)
		throw std::exception("This is a singleplayer game!");

	instance = this;

	InitializeData();

	InitializeAnimation();

}

void Player::PlayerRender() {

	GetComponent<AnimationController>()->RenderCurrent(
		transform->position,
		transform->scale,
		Math::RadToDeg(forward.Angle())
	);

	GetComponent<BoxCollider>()->Debug();

}

void Player::DisableInteraction() {

	canInteract = false;

}

void Player::EnableInteraction() {

	canInteract = true;

}

void Player::Update() {

	if (canInteract) {

		HandleMovement();

		HandleFacing();

		HandleActions();

	}

	HandleStamina();

}

void Player::GiveItem(ItemIndex itemIndex, int amount) {

	GetComponent<Inventory>()->AddItem(itemIndex, amount);

}

int Player::GetAmmoCount(AmmunitionID ammunitionID) {

	return GetComponent<Inventory>()->GetItemCount(Ammunition::AMMO_ITEM_INDEX_MAP.at(ammunitionID));

}

bool Player::TryConsumeAmmo(AmmunitionID ammunitionID, int amount) {

	return GetComponent<Inventory>()->TryRemoveItem(Ammunition::AMMO_ITEM_INDEX_MAP.at(ammunitionID), amount);

}

std::vector<Firearm*> Player::GetFirearmList() {

	return GetComponent<Inventory>()->GetItemListOfType<Firearm>();

}

Vector2 Player::GetForward() const { return forward; }

Vector2 Player::GetAimingDirection() {

	return forward.Rotate(Math::DegToRad(Random::Sign(Random::Float(0.0f, aimDeviation))));

}

Player* Player::Instance() { return instance; }