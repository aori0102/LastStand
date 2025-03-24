/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Zombie.h>

#include <GameComponent.h>
#include <GameCore.h>
#include <GameManager.h>
#include <MediaManager.h>
#include <Player.h>
#include <Texture.h>
#include <WaveManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float ZombieAttribute::DAMAGE_MULTIPLIER = 1.03f;
const float ZombieAttribute::HEALTH_MULTIPLIER = 1.07f;
const float ZombieAttribute::EXP_MULTIPLIER = 1.01f;

const float Zombie::KNOCKBACK_FORCE = 50.0f;
const float Zombie::HEALTH_BAR_VERTICAL_OFFSET = 50.0f;
const float Zombie::HEALTH_BAR_SCALE = 0.4f;
const std::unordered_map<ZombieIndex, ZombieAttribute> Zombie::ZOMBIE_BASE_ATTRIBUTE_MAP = {
	{ ZombieIndex::Normal, ZombieAttribute(60.0f, 32.0f, 6.0f, 3.0f) },
	{ ZombieIndex::Bomber, ZombieAttribute(54.0f, 73.0f, 9.0f, 5.0f) },
	{ ZombieIndex::Lurker, ZombieAttribute(104.0f, 21.0f, 3.0f, 7.0f) },
	{ ZombieIndex::Tanker, ZombieAttribute(30.0f, 148.0f, 3.0f, 9.0f) },
};
const std::unordered_map<ZombieIndex, SDL_Rect> Zombie::ZOMBIE_SPRITE_CLIP_MAP = {
	{ ZombieIndex::Normal, { 16, 16, 96, 96 } },
	{ ZombieIndex::Bomber, { 16, 16, 96, 96 } },
	{ ZombieIndex::Lurker, { 32, 144, 80, 80 } },
	{ ZombieIndex::Tanker, { 16, 16, 96, 96 } },
};

Zombie::Zombie(GameObject* initTarget, ZombieIndex initZombieIndex) : GameObject("Zombie", Layer::Zombie) {

	zombieIndex = initZombieIndex;

	zombieAttribute = new ZombieAttribute(
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed,
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).health,
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).damage,
		ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).exp
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

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->drag = 10.0f;
	rigidBody->mass = 60.0f;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(zombieAttribute->health);
	humanoid->OnDeath = [this]() {
		GameObject::Destroy(this);
		};

	Image* image = AddComponent<Image>();
	image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Zombie), false);
	image->showOnScreen = false;
	image->clip = ZOMBIE_SPRITE_CLIP_MAP.at(zombieIndex);

	transform->scale = Vector2(50.0f, 50.0f);

	// Initialize health bar
	healthBar = new GameObject();
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_HealthBar), true);
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar_image->fillAmount = 1.0f;
	healthBar_image->showOnScreen = false;
	healthBar->transform->scale *= HEALTH_BAR_SCALE;

	target = initTarget;
	//movementSpeed = 100.0f;

	Render = [image, healthBar_image, humanoid, this, boxCollider]() {

		image->Render();

		// Render health bar
		healthBar_image->transform->position = transform->position + Vector2::up * HEALTH_BAR_VERTICAL_OFFSET;
		healthBar_image->fillAmount = humanoid->GetHealth() / humanoid->GetMaxHealth();
		healthBar_image->Render();

		boxCollider->Debug();

		};

}

void Zombie::Update() {

	if (target) {

		Vector2 forward = (target->transform->position - transform->position).Normalize();

		transform->Translate(
			forward * GameCore::DeltaTime() * ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed
		);

		// Calculate rotation
		GetComponent<Image>()->angle = Math::RadToDeg(forward.Angle());

	}

}

void Zombie::OnDestroy() {

	GameManager::Instance()->ReportDead(this);

}

void Zombie::OnCollisionEnter(BoxCollider* other) {

	if (!other->Owner()->IsA<Player>())
		return;

	Humanoid* humanoid = nullptr;
	RigidBody* rigidBody = nullptr;

	if (other->TryGetComponent<Humanoid>(humanoid))
		humanoid->Damage(zombieAttribute->damage);

	if (other->TryGetComponent<RigidBody>(rigidBody))
		rigidBody->AddForce((other->transform->position - transform->position).Normalize() * KNOCKBACK_FORCE);

}

float Zombie::GetExp() const {

	return zombieAttribute->exp * ZombieAttribute::EXP_MULTIPLIER
		* (
			WaveHandler::Instance()->GetDifficulty() * logf(WaveHandler::Instance()->GetCurrentWave() +
			sqrtf(powf(ZombieAttribute::EXP_MULTIPLIER, WaveHandler::Instance()->GetCurrentWave())))
			);

}