#include <Zombie.h>
#include <Game.h>
#include <GameManager.h>
#include <Texture.h>
#include <GameComponent.h>
#include <WaveHandler.h>

const string Zombie::SPRITE_PATH = "./Asset/Zombie.png";
const std::unordered_map<ZombieIndex, ZombieAttribute> Zombie::ZOMBIE_BASE_ATTRIBUTE_MAP = {
	{ ZombieIndex::Normal, ZombieAttribute(60.0f, 32.0f, 6.0f) },
	{ ZombieIndex::Bomber, ZombieAttribute(54.0f, 73.0f, 9.0f) },
	{ ZombieIndex::Lurker, ZombieAttribute(104.0f, 21.0f, 3.0f) },
	{ ZombieIndex::Tanker, ZombieAttribute(30.0f, 148.0f, 3.0f) },
};
const Vector2 Zombie::HEALTH_BAR_SCALE = Vector2(100.0f, 10.0f);
const float Zombie::HEALTH_BAR_VERTICAL_OFFSET = 50.0f;
const std::string Zombie::HEALTH_BAR_PATH = "./Asset/HealthBar.png";

const float ZombieAttribute::DAMAGE_MULTIPLIER = 1.03f;
const float ZombieAttribute::HEALTH_MULTIPLIER = 1.07f;

Zombie::Zombie(GameObject* initTarget, ZombieIndex initZombieIndex) : GameObject("Zombie", Layer::Zombie) {

	zombieIndex = initZombieIndex;

	zombieAttribute = new ZombieAttribute(
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed,
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).health,
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).damage
	);
	// Calculation of zombie's attribute uses the following formula
	// y = bm(d * ln(x) + sqrt(m ^ x))
	// Where
	// b is the base attribute
	// m is the attribute's multiplier
	// d is the difficulty coefficient 
	// x is the wave
	zombieAttribute->health *= ZombieAttribute::HEALTH_MULTIPLIER
		* (
			WaveHandler::Instance()->GetDifficulty() * std::logf(WaveHandler::Instance()->GetCurrentWave()) +
			std::sqrtf(std::powf(ZombieAttribute::HEALTH_MULTIPLIER, WaveHandler::Instance()->GetCurrentWave()))
			);
	zombieAttribute->damage *= ZombieAttribute::DAMAGE_MULTIPLIER
		* (
			WaveHandler::Instance()->GetDifficulty() * std::logf(WaveHandler::Instance()->GetCurrentWave()) +
			std::sqrtf(std::powf(ZombieAttribute::DAMAGE_MULTIPLIER, WaveHandler::Instance()->GetCurrentWave()))
			);

	transform->position = Vector2(500.0, 200.0f);
	transform->scale = Vector2(50.0f, 50.0f);

	AddComponent<BoxCollider>();
	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(zombieAttribute->health);

	Image* zombieSprite = AddComponent<Image>();
	zombieSprite->LoadImage(SPRITE_PATH);
	zombieSprite->showOnScreen = false;

	// Initialize health bar
	healthBar = new GameObject();
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LoadImage(HEALTH_BAR_PATH);
	healthBar_image->transform->scale = HEALTH_BAR_SCALE;
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar_image->fillAmount = 1.0f;
	healthBar_image->showOnScreen = false;

	target = initTarget;
	//movementSpeed = 100.0f;

	Render = [zombieSprite, healthBar_image, humanoid, this]() {

		zombieSprite->Render();

		// Render health bar
		healthBar_image->transform->position = transform->position + Vector2::up * HEALTH_BAR_VERTICAL_OFFSET;
		healthBar_image->fillAmount = humanoid->GetHealth() / humanoid->GetMaxHealth();
		healthBar_image->Render();

		};

}

void Zombie::Update() {

	if (target) {

		Transform* transform = GetComponent<Transform>();

		transform->Translate(
			(target->GetComponent<Transform>()->position - transform->position).Normalize() * Game::DeltaTime() * ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed
		);

	}

}

void Zombie::OnDestroy() {

	GameManager::Instance()->ReportDead(this);

}