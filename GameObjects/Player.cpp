/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <functional>

#include <Animation.h>
#include <Firearm.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <MediaManager.h>
#include <PhysicsManager.h>
#include <Player.h>
#include <PlayerUI.h>
#include <Projectile.h>
#include <Texture.h>
#include <Type.h>

const float Player::MAX_AIMING_DEVIATION = 27.0f;

void Player::HandleActions() {

	if (GameCore::SelectedUI())
		return;

	// Use action
	if (GameCore::GetMouseState(MouseButton::Left).started)
		usingItem = true;
	else if (GameCore::GetMouseState(MouseButton::Left).canceled)
		usingItem = false;

	// Aiming
	if (GameCore::GetMouseState(MouseButton::Right).started)
		GameCore::SetCameraZoom(1.3f);
	else if (GameCore::GetMouseState(MouseButton::Right).canceled)
		GameCore::SetCameraZoom(1.0f);

	// Reload current firearm
	if (GameCore::GetKeyState(SDLK_r).started)
		firearm->Reload();

	if (usingItem) {

		// Shoot firearm
		if (firearm->Use(this)) {

			currentAnimationState = AnimationIndex::Shoot;
			currentAnimationStartTick = GameCore::Time();
			currentAnimationTime = animationMap[AnimationIndex::Shoot]->GetAnimationLength();

		}

	}

}

void Player::HandleMovement(Transform* transform) {

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

void Player::HandleFacing(Transform* transform) {

	// Calculate rotation
	forward = (GameCore::ScreenToWorldPosition(GameCore::GetMouseInput()) - transform->position).Normalize();

	// Render line of sight
	GameCore::DrawLine(transform->position, forward, 2000.0f, Color::GREEN);

}

Player::Player() : GameObject("Player", Layer::Player) {

	InitializeData();

	InitializeAnimation();

}

void Player::InitializeAnimation() {

	// Idle
	animationMap[AnimationIndex::Idle] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), GetLayer());
	animationMap[AnimationIndex::Idle]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 16, 16, 160, 160 }, 0.0f, 3.0f
	));

	// Shoot
	animationMap[AnimationIndex::Shoot] = new AnimationClip(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player), GetLayer());
	animationMap[AnimationIndex::Shoot]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 208, 16, 160, 160 }, 0.0f, 3.0f
	));
	animationMap[AnimationIndex::Shoot]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 208, 16, 160, 160 }, 0.1f, 3.0f
	));

}

void Player::InitializeData() {

	movementSpeed = 700.0f;

	canInteract = true;
	usingItem = false;
	isMoving = false;

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Player));
	playerSprite->showOnScreen = false;

	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());

	Transform* transform = AddComponent<Transform>();
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->mass = 60.0f;
	rigidBody->drag = 6.0f;

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(250.0f);
	humanoid->OnDeath = []() {
		std::cout << "Player dead" << std::endl;
		};
	// Add a firearm to the inventory
	firearm = new Firearm(80, 200, 400.0f, 5.0f);

	animationMap = {};

	currentAnimationState = AnimationIndex::Idle;
	currentAnimationStartTick = 0.0f;
	currentAnimationTime = 0.0f;

	Render = [this]() { PlayerRender(); };

}

void Player::PlayerRender() {

	std::cout << "Player rendering..." << std::endl;

	if (currentAnimationState != AnimationIndex::Idle && GameCore::Time() >= currentAnimationStartTick + currentAnimationTime) {

		currentAnimationState = AnimationIndex::Idle;
		currentAnimationTime = animationMap[AnimationIndex::Idle]->GetAnimationLength();
		currentAnimationStartTick = GameCore::Time();

	}

	Transform* transform = GetComponent<Transform>();

	animationMap[currentAnimationState]->RenderCurrent(
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

		Transform* transform = GetComponent<Transform>();

		HandleMovement(transform);

		HandleFacing(transform);

		HandleActions();

	}

}

Vector2 Player::GetForward() const { return forward; }

Vector2 Player::GetAimingDirection() {

	Vector2 aimDirection = forward;

	if (isMoving)
		aimDirection = aimDirection.Rotate(Math::DegToRad(Random::Sign(Random::Float(0.0f, MAX_AIMING_DEVIATION))));

	return aimDirection;

}

Firearm* Player::GetFirearm() const { return firearm; }