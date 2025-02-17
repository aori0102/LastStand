#include <Enemy.h>
#include <Game.h>
#include <GameManager.h>

const string ENEMY_SPRITE_PATH = "./Asset/Zombie.png";

// Health bar data
const Vector2 HEALTH_BAR_SCALE = Vector2(100.0f, 10.0f);
const float HEALTH_BAR_VERTICAL_OFFSET = 50.0f;
const string HEALTH_BAR_PATH = "./Asset/HealthBar.png";

Enemy::Enemy(GameObject* initTarget) {

	Transform* transform = AddComponent<Transform>();
	transform->position = Vector2(500.0, 200.0f);
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	AddComponent<Humanoid>();

	Image* enemySprite = AddComponent<Image>();
	enemySprite->LoadImage(ENEMY_SPRITE_PATH);
	enemySprite->pivot = Vector2(0.5f, 0.5f);
	enemySprite->showOnScreen = false;

	// Initialize health bar
	healthBar = new GameObject();
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LoadImage(HEALTH_BAR_PATH);
	healthBar_image->GetOwner()->GetComponent<Transform>()->scale = HEALTH_BAR_SCALE;
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar_image->fillAmount = 1.0f;
	healthBar_image->showOnScreen = false;

	target = initTarget;
	movementSpeed = 300.0f;

}

void Enemy::Render() {

	Transform* transform = GetComponent<Transform>();
	Image* enemySprite = GetComponent<Image>();

	enemySprite->GetOwner()->GetComponent<Transform>()->position = GetComponent<Transform>()->position;
	enemySprite->Render();

	GetComponent<BoxCollider>()->Debug();

	// Render health bar
	Image* healthBar_image = healthBar->GetComponent<Image>();
	Humanoid* humanoid = GetComponent<Humanoid>();
	healthBar_image->GetOwner()->GetComponent<Transform>()->position = transform->position + Vector2::up * HEALTH_BAR_VERTICAL_OFFSET;
	healthBar_image->fillAmount = humanoid->GetHealth() / humanoid->GetMaxHealth();
	healthBar_image->Render();

}

void Enemy::Update() {

	if (target) {

		Transform* transform = GetComponent<Transform>();

		transform->Translate(
			(target->GetComponent<Transform>()->position - transform->position).Normalize() * Game::GetDeltaTime() * movementSpeed
		);

	}

	Render();

}

void Enemy::OnDestroy() {

	GameManager::ReportDead(this);

}