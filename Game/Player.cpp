#include <Player.h>
#include <GameComponent.h>
#include <Game.h>
#include <Type.h>
#include <Projectile.h>
#include <Physics.h>
#include <Item.h>
#include <PlayerUI.h>
#include <Texture.h>
#include <Animation.h>

const string PLAYER_SPRITE_PATH = "./Asset/PlayerSprite.png";

Player::Player() {

	movementSpeed = 700.0f;

	canInteract = true;

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LoadImage(PLAYER_SPRITE_PATH);
	playerSprite->pivot = Vector2(0.5f, 0.5f);
	playerSprite->showOnScreen = false;

	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());

	Transform* transform = AddComponent<Transform>();
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();

	// Add a firearm to the inventory
	firearm = new Firearm(8, 20, 400.0f, 5.0f);

	animationMap = {};

	currentAnimationState = AnimationIndex::Idle;
	currentAnimationStartTick = 0.0f;
	currentAnimationTime = 0.0f;

	InitializeAnimation();

}

void Player::Update() {

	if (canInteract) {

		Transform* transform = GetComponent<Transform>();

		HandleMovement(transform);

		HandleFacing(transform);

		HandleActions();

	}

	// Render
	Render();

}

void Player::Render() {

	if (currentAnimationState != AnimationIndex::Idle && Game::Time() >= currentAnimationStartTick + currentAnimationTime) {

		currentAnimationState = AnimationIndex::Idle;
		currentAnimationTime = animationMap[AnimationIndex::Idle]->AnimationLength();
		currentAnimationStartTick = Game::Time();

	}

	Transform* transform = GetComponent<Transform>();

	animationMap[currentAnimationState]->RenderCurrent(
		transform->position,
		transform->scale,
		-Math::RadToDeg(forward.Angle())
	);

	GetComponent<BoxCollider>()->Debug();

}

Vector2 Player::Forward() const { return forward; }

void Player::HandleMovement(Transform* transform) {

	// Input
	Vector2 input(0.0f, 0.0f);

	if (Game::GetKeyState(SDLK_w).performed)
		input += Vector2::up;

	if (Game::GetKeyState(SDLK_a).performed)
		input += Vector2::left;

	if (Game::GetKeyState(SDLK_s).performed)
		input += Vector2::down;

	if (Game::GetKeyState(SDLK_d).performed)
		input += Vector2::right;

	// Apply movement
	transform->Translate(input.Normalize() * movementSpeed * Game::DeltaTime());

}

void Player::HandleFacing(Transform* transform) {

	// Calculate rotation
	forward = (Game::ScreenToWorldPosition(Game::GetMouseInput()) - transform->position).Normalize();

	// Render line of sight
	Game::DrawLine(transform->position, forward, 2000.0f, Color::GREEN);

}

void Player::HandleActions() {

	// Use action
	if (Game::GetMouseState(MouseButton::Left).performed) {

		if (firearm->Use(this)) {

			currentAnimationState = AnimationIndex::Shoot;
			currentAnimationStartTick = Game::Time();
			currentAnimationTime = animationMap[AnimationIndex::Shoot]->AnimationLength();

		}

	}

	// Reload current firearm
	if (Game::GetKeyState(SDLK_r).started)
		firearm->Reload();

}

void Player::DisableInteraction() {

	canInteract = false;

}

void Player::EnableInteraction() {

	canInteract = true;

}

Firearm* Player::GetFirearm() { return firearm; }

void Player::InitializeAnimation() {

	// Idle
	animationMap[AnimationIndex::Idle] = new AnimationClip(GetComponent<Image>());
	animationMap[AnimationIndex::Idle]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 16, 16, 160, 160 }, 0.0f, 3.0f
	));

	// Shoot
	animationMap[AnimationIndex::Shoot] = new AnimationClip(GetComponent<Image>());
	animationMap[AnimationIndex::Shoot]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 208, 16, 160, 160 }, 0.0f, 3.0f
	));
	animationMap[AnimationIndex::Shoot]->AddAnimationFrame(new AnimationClip::AnimationFrame(
		{ 208, 16, 160, 160 }, 0.1f, 3.0f
	));

}