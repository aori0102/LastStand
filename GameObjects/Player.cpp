﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Player.h>

#include <functional>

#include <AnimationManager.h>
#include <Animation.h>
#include <Item.h>
#include <Firearm.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <PlayerUI.h>
#include <Projectile.h>
#include <Texture.h>
#include <Type.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float Player::MAX_AIMING_DEVIATION = 27.0f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Player::HandleActions() {

	if (GameCore::SelectedUI())
		return;

	// Aiming
	if (GameCore::GetMouseState(MouseButton::Right).started)
		GameCore::SetCameraZoom(1.3f);
	else if (GameCore::GetMouseState(MouseButton::Right).canceled)
		GameCore::SetCameraZoom(1.0f);

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

	std::cout << (int)itemIndex << std::endl;

	// Use item
	usingItem = GameCore::GetMouseState(MouseButton::Left).started;

}

void Player::HandleMovement() {

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
	transform->Translate(input.Normalize() * movementSpeed * GameCore::DeltaTime());

}

void Player::HandleFacing() {

	// Calculate rotation
	forward = (GameCore::ScreenToWorldPosition(GameCore::GetMouseInput()) - transform->position).Normalize();

}

void Player::InitializeData() {

	movementSpeed = 700.0f;

	itemIndex = ItemIndex::None;

	canInteract = true;
	usingItem = false;
	isMoving = false;

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), false);
	playerSprite->showOnScreen = false;

	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());

	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	Inventory* inventory = AddComponent<Inventory>();
	inventory->AddItem(ItemIndex::Pistol);
	inventory->AddItem(ItemIndex::Shotgun);

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->mass = 60.0f;
	rigidBody->drag = 6.0f;

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(250.0f);
	humanoid->OnDeath = []() {
		std::cout << "Player dead" << std::endl;
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

	animController->MakeDefault(AnimationIndex::Player_Idle);

	animController->AddTransition(
		AnimationIndex::Player_Idle,
		AnimationIndex::Player_Pistol_Idle,
		[this]() {
			return itemIndex == ItemIndex::Pistol;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Idle,
		AnimationIndex::Player_Shotgun_Idle,
		[this]() {
			return itemIndex == ItemIndex::Shotgun;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Idle,
		AnimationIndex::Player_Idle,
		[this]() {
			return itemIndex == ItemIndex::None;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Idle,
		AnimationIndex::Player_Idle,
		[this]() {
			return itemIndex == ItemIndex::None;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Idle,
		AnimationIndex::Player_Pistol_Shoot,
		[this]() {
			return itemIndex == ItemIndex::Pistol && usingItem;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Shoot,
		AnimationIndex::Player_Pistol_Idle
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Idle,
		AnimationIndex::Player_Shotgun_Shoot,
		[this]() {
			return itemIndex == ItemIndex::Shotgun && usingItem;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Shoot,
		AnimationIndex::Player_Shotgun_Idle
	);

	animController->AddTransition(
		AnimationIndex::Player_Pistol_Idle,
		AnimationIndex::Player_Shotgun_Idle,
		[this]() {
			return itemIndex == ItemIndex::Shotgun;
		}
	);

	animController->AddTransition(
		AnimationIndex::Player_Shotgun_Idle,
		AnimationIndex::Player_Pistol_Idle,
		[this]() {
			return itemIndex == ItemIndex::Pistol;
		}
	);

}

Player::Player() : GameObject("Player", Layer::Player) {

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

}

Vector2 Player::GetForward() const { return forward; }

Vector2 Player::GetAimingDirection() const {

	Vector2 aimDirection = forward;

	if (isMoving)
		aimDirection = aimDirection.Rotate(Math::DegToRad(Random::Sign(Random::Float(0.0f, MAX_AIMING_DEVIATION))));

	return aimDirection;

}