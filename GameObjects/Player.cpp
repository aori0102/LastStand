/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Player.h>

#include <functional>

#include <Ammunition.h>
#include <AnimationController.h>
#include <AnimationManager.h>
#include <AudioManager.h>
#include <BoxCollider.h>
#include <Bullet.h>
#include <DataManager.h>
#include <Firearm.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <GameManager.h>
#include <HotBar.h>
#include <HotBarUI.h>
#include <Humanoid.h>
#include <Inventory.h>
#include <InventoryUI.h>
#include <Item.h>
#include <ItemManager.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <RigidBody.h>
#include <Shop.h>
#include <Texture.h>
#include <Transform.h>
#include <Utils.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const std::unordered_map<PlayerAttribute, float> Player::DEFAULT_PLAYER_ATTRIBUTE_MAP = {
	{ PlayerAttribute::Accuracy, 0.3f },
	{ PlayerAttribute::ReloadSpeed, 1.0f },
	{ PlayerAttribute::MaxHealth, 100.0f },
};

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
	if (GameCore::GetKeyState(SDLK_1).started)
		HotBar::Instance()->SelectSlot(HotBarSlotIndex::First);
	else if (GameCore::GetKeyState(SDLK_2).started)
		HotBar::Instance()->SelectSlot(HotBarSlotIndex::Second);
	else if (GameCore::GetKeyState(SDLK_3).started)
		HotBar::Instance()->SelectSlot(HotBarSlotIndex::Third);
	else if (GameCore::GetKeyState(SDLK_4).started)
		HotBar::Instance()->SelectSlot(HotBarSlotIndex::Forth);
	else if (GameCore::GetKeyState(SDLK_5).started)
		HotBar::Instance()->SelectSlot(HotBarSlotIndex::Fifth);

	itemIndex = HotBar::Instance()->GetSelectedItemIndex();

	// Use item
	if (itemIndex == ItemIndex::Rifle_M4)
		usingItem = GameCore::GetMouseState(MouseButton::Left).performed;
	else
		usingItem = GameCore::GetMouseState(MouseButton::Left).started;

	usingItem = usingItem && Inventory::Instance()->TryUseCurrent();

	// Toggle inventory UI
	if (GameCore::GetActionState(ActionIndex::ToggleInventory).started)
		Inventory::Instance()->ToggleInventory();

	// Reload firearm
	if (GameCore::GetActionState(ActionIndex::Reload).started) {

		Item* currentItem = HotBar::Instance()->GetSelectedItem();
		Firearm* currentFirearm = nullptr;
		if (currentItem)
			currentFirearm = dynamic_cast<Firearm*>(currentItem);

		if (currentFirearm)
			currentFirearm->Reload();

	}

	// Sprint
	if (GameCore::GetActionState(ActionIndex::Sprint).started)
		isSprinting = true;
	else if (GameCore::GetActionState(ActionIndex::Sprint).canceled)
		isSprinting = false;

	// Shop
	if (GameCore::GetActionState(ActionIndex::ToggleShop).started)
		Shop::Instance()->Toggle();

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

	if (GameCore::GetActionState(ActionIndex::MoveUp).performed)
		input += Vector2::up;

	if (GameCore::GetActionState(ActionIndex::MoveLeft).performed)
		input += Vector2::left;

	if (GameCore::GetActionState(ActionIndex::MoveDown).performed)
		input += Vector2::down;

	if (GameCore::GetActionState(ActionIndex::MoveRight).performed)
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

	// Play movement sound
	float currentTick = GameCore::Time();
	MediaSFX audioIndex = static_cast<MediaSFX>(
		Random::Int(static_cast<int>(MediaSFX::WalkGrass1), static_cast<int>(MediaSFX::WalkGrass3))
		);

	if (isMoving) {

		if (isSprinting) {

			if (currentTick >= lastWalkSoundTick + SPRINT_SOUND_DELAY) {

				lastWalkSoundTick = currentTick;
				AudioManager::Instance()->PlayOneShot(audioIndex);

			}

		} else if (isAiming) {

			if (currentTick >= lastWalkSoundTick + AIM_SOUND_DELAY) {

				lastWalkSoundTick = currentTick;
				AudioManager::Instance()->PlayOneShot(audioIndex);

			}


		} else {

			if (currentTick >= lastWalkSoundTick + WALK_SOUND_DELAY) {

				lastWalkSoundTick = currentTick;
				AudioManager::Instance()->PlayOneShot(audioIndex);

			}

		}

	}

}

void Player::HandleFacing() {

	// Calculate rotation
	forward = (GameCore::ScreenToWorldPosition(GameCore::GetMouseInput()) - transform->position).Normalize();

}

void Player::HandleStamina() {

	Humanoid* humanoid = GetComponent<Humanoid>();

	if (isMoving && isSprinting)
		humanoid->DrainStamina(STAMINA_DRAIN_RATE * GameCore::DeltaTime());
	else
		humanoid->GainStamina(STAMINA_RECOVERY_RATE * GameCore::DeltaTime());

}

void Player::HandleVisual() {

	if (isHurtDisplay && GameCore::Time() >= lastHurtTick + HURT_VISUAL_DISPLAY_TIME) {

		isHurtDisplay = false;
		MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player)->SetColorMod(Color::WHITE);

	}

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
	
	isMoving = false;
	isAiming = false;
	isSprinting = false;
	usingItem = false;
	isHurtDisplay = false;
	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());
	currentMovementSpeed = DEFAULT_MOVEMENT_SPEED;
	targetMovementSpeed = DEFAULT_MOVEMENT_SPEED;
	aimDeviation = STANDING_AIM_DEVIATION;
	lastWalkSoundTick = 0.0f;
	lastHurtTick = 0.0f;
	itemIndex = ItemIndex::None;
	forward = Vector2::zero;

	usingItem = false;
	currentAnimationTime = 0.0f;
	currentAnimationStartTick = 0.0f;

	Render = [this]() { PlayerRender(); };

}

void Player::InitializeComponents() {

	transform->scale = Vector2(50.0f, 50.0f);
	AddComponent<BoxCollider>()->ignoreLayerSet = { Layer::Bullet };

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), false);
	playerSprite->showOnScreen = false;

	inventoryUI = GameObject::Instantiate<InventoryUI>("Inventory UI", Layer::Menu);
	inventoryUI->Disable();

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->mass = 60.0f;
	rigidBody->drag = 6.0f;

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->OnDeath = [this]() {
		GameManager::Instance()->ReportDead(this);
		};
	humanoid->OnDamaged = [this]() {
		isHurtDisplay = true;
		lastHurtTick = GameCore::Time();
		MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player)->SetColorMod(Color::RED);
		};

}

void Player::LoadData() {

	PlayerSaveData* data = DataManager::Instance()->playerSaveData;

	playerAttributeMap = data->playerAttribute;
	for (auto it = data->playerAttribute.begin(); it != data->playerAttribute.end(); it++)
		SetAttribute(it->first, it->second);

	GetComponent<Humanoid>()->SetHealth(data->health);

}

void Player::SaveData() {

	PlayerSaveData* data = DataManager::Instance()->playerSaveData;

	data->playerAttribute = playerAttributeMap;

	Humanoid* humanoid = GetComponent<Humanoid>();
	data->health = humanoid->GetHealth();

}

void Player::Reset() {

	Humanoid* humanoid = GetComponent<Humanoid>();
	humanoid->SetHealth(100.0f);
	humanoid->SetMaxHealth(100.0f);

	playerAttributeMap = DEFAULT_PLAYER_ATTRIBUTE_MAP;

	transform->position = Vector2::zero;

}

Player::Player() : GameObject("Player", Layer::Player) {

	if (instance)
		throw std::exception("This is a singleplayer game!");

	instance = this;

	InitializeComponents();
	InitializeData();
	InitializeAnimation();
	
}

Player::~Player() {

	GameObject::Destroy(inventoryUI);
	inventoryUI = nullptr;

	playerAttributeMap.clear();

	instance = nullptr;

}

void Player::PlayerRender() {

	float angle = forward.Angle();
	GetComponent<AnimationController>()->RenderCurrent(
		transform->position,
		transform->scale,
		Math::RadToDeg(angle),
		std::cosf(angle) < 0 ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE
	);

	GetComponent<BoxCollider>()->Debug();

}

void Player::GiveItem(ItemIndex itemIndex, int amount) {

	Inventory::Instance()->AddItem(itemIndex, amount);

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
				firearm->GetIndex(), FirearmAttributeIndex::ReloadTime, 1.0f / value
			);

		break;

	}

	case PlayerAttribute::Accuracy: {

		std::vector<Firearm*> firearmList = GetFirearmList();
		for (Firearm* firearm : firearmList)
			firearm->ModifyAttributeMultiplier(
				firearm->GetIndex(), FirearmAttributeIndex::CriticalChance, value
			);

		break;

	}

	}

}

void Player::Update() {

	if (!GameManager::Instance()->GameRunning())
		return;

	HandleVisual();
	HandleMovement();
	HandleFacing();
	HandleActions();
	HandleStamina();

}

int Player::GetAmmoCount(ItemIndex ammoItemIndex) {

	return Inventory::Instance()->GetItemCount(ammoItemIndex);

}

float Player::GetAttribute(PlayerAttribute playerAttribute) { return playerAttributeMap.at(playerAttribute); }

bool Player::TryConsumeAmmo(ItemIndex ammoItemIndex, int amount) {

	return Inventory::Instance()->TryRemoveItem(ammoItemIndex, amount);

}

Vector2 Player::GetAimingDirection() {

	return forward.Rotate(Math::DegToRad(Random::Sign(Random::Float(0.0f, aimDeviation))));

}

std::vector<Firearm*> Player::GetFirearmList() {

	return Inventory::Instance()->GetItemListOfType<Firearm>();

}

Player* Player::Instance() { return instance; }