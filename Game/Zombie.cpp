#include <Zombie.h>
#include <Game.h>
#include <GameManager.h>
#include <Texture.h>
#include <GameComponent.h>

const string ENEMY_SPRITE_PATH = "./Asset/Zombie.png";

// Health bar data
const Vector2 HEALTH_BAR_SCALE = Vector2(100.0f, 10.0f);
const float HEALTH_BAR_VERTICAL_OFFSET = 50.0f;
const string HEALTH_BAR_PATH = "./Asset/HealthBar.png";

Zombie::Zombie(GameObject* initTarget) : GameObject("Zombie", Layer::Zombie) {

	Transform* transform = AddComponent<Transform>();
	transform->position = Vector2(500.0, 200.0f);
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	Humanoid* humanoid = AddComponent<Humanoid>();

	Image* zombieSprite = AddComponent<Image>();
	zombieSprite->LoadImage(ENEMY_SPRITE_PATH);
	zombieSprite->showOnScreen = false;

	// Initialize health bar
	healthBar = new GameObject();
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LoadImage(HEALTH_BAR_PATH);
	healthBar_image->GetComponent<Transform>()->scale = HEALTH_BAR_SCALE;
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar_image->fillAmount = 1.0f;
	healthBar_image->showOnScreen = false;

	target = initTarget;
	movementSpeed = 100.0f;

	Render = [zombieSprite, healthBar_image, humanoid, this]() {

		zombieSprite->Render();

		// Render health bar
		healthBar_image->GetComponent<Transform>()->position = GetComponent<Transform>()->position + Vector2::up * HEALTH_BAR_VERTICAL_OFFSET;
		healthBar_image->fillAmount = humanoid->Health() / humanoid->maxHealth;
		healthBar_image->Render();

		};

}

void Zombie::Update() {

	if (target) {

		Transform* transform = GetComponent<Transform>();

		transform->Translate(
			(target->GetComponent<Transform>()->position - transform->position).Normalize() * Game::DeltaTime() * movementSpeed
		);

	}

	Render();

}

void Zombie::OnDestroy() {

	GameManager::Instance()->ReportDead(this);

}