#include <Player.h>
#include <GameComponent.h>
#include <Game.h>
#include <Type.h>
#include <Projectile.h>
#include <Physics.h>
#include <Item.h>
#include <PlayerUI.h>

const string PLAYER_SPRITE_PATH = "./Asset/Character.png";

Player::Player() {

	movementSpeed = 700.0f;

	Image* playerSprite = AddComponent<Image>();
	playerSprite->LoadImage(PLAYER_SPRITE_PATH);
	playerSprite->pivot = Vector2(0.5f, 0.5f);

	playerForwardAngle = Math::RadToDeg(Vector2::up.Angle());

	Transform* transform = AddComponent<Transform>();
	transform->position = Vector2(100.0f, 100.0f);
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	Inventory* inventory = AddComponent<Inventory>();

	// Add a firearm to the inventory
	Firearm* firearm = new Firearm(8, 20, 400.0f, 5.0f);
	inventory->AddItem(firearm);

}

void Player::Update() {

	// Input
	Vector2 input(0.0f, 0.0f);

	if (Game::GetKeyState(SDLK_w).started)
		input += Vector2::up;

	if (Game::GetKeyState(SDLK_a).started)
		input += Vector2::left;

	if (Game::GetKeyState(SDLK_s).started)
		input += Vector2::down;

	if (Game::GetKeyState(SDLK_d).started)
		input += Vector2::right;

	// Get component
	Transform* transform = GetComponent<Transform>();

	// Apply movement
	transform->Translate(input.Normalize() * movementSpeed * Game::deltaTime);

	// Calculate rotation
	forward = (Game::GetMouseInput() - transform->position).Normalize();
	GetComponent<Image>()->angle = playerForwardAngle - Math::RadToDeg(forward.Angle());

	// Render line of sight
	Vector2 sightEndPoint = transform->position + forward.Normalize() * 1000.0f;
	Game::DrawLine(transform->position, sightEndPoint, Color::GREEN);

	HandleActions();

	// Render
	Render();

}

void Player::Render() {

	Image* playerSprite = GetComponent<Image>();

	playerSprite->GetOwner()->GetComponent<Transform>()->position = GetComponent<Transform>()->position;
	playerSprite->Render();

	GetComponent<BoxCollider>()->Debug();

}

Vector2 Player::GetForward() const {

	return forward;

}

void Player::HandleActions() {

	// Get player inventory
	Inventory* inventory = GetComponent<Inventory>();

	// Use action
	if (Game::GetMouseState(MouseButton::Left).started)
		inventory->UseCurrent(this);

	// Reload current firearm
	if (Game::GetKeyState(SDLK_r).started) {

		// Get the item
		Firearm* firearm = dynamic_cast<Firearm*>(inventory->GetCurrentItem());

		// Reload
		if (firearm)
			firearm->Reload();

	}

}