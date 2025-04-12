/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Zombie.h>

#include <AudioManager.h>
#include <GameComponent.h>
#include <GameCore.h>
#include <GameManager.h>
#include <Humanoid.h>
#include <MediaManager.h>
#include <Player.h>
#include <RigidBody.h>
#include <Texture.h>
#include <Transform.h>
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
const float Zombie::GROAN_SOUND_DELAY_MIN = 4.7f;
const float Zombie::GROAN_SOUND_DELAY_MAX = 9.9f;
const std::unordered_map<ZombieIndex, ZombieAttribute> Zombie::ZOMBIE_BASE_ATTRIBUTE_MAP = {
	{ ZombieIndex::Normal, ZombieAttribute{
		.movementSpeed = 60.0f,
		.health = 32.0f,
		.damage = 6.0f,
		.exp = 3.0f
		}
	},
	{ ZombieIndex::Lurker, ZombieAttribute{
		.movementSpeed = 104.0f,
		.health = 21.0f,
		.damage = 3.0f,
		.exp = 7.0f
		}
	},
	{ ZombieIndex::Bomber, ZombieAttribute{
		.movementSpeed = 54.0f,
		.health = 73.0f,
		.damage = 9.0f,
		.exp = 5.0f
		}
	},
	{ ZombieIndex::Tanker, ZombieAttribute{
		.movementSpeed = 30.0f,
		.health = 148.0f,
		.damage = 3.0f,
		.exp = 9.0f
		}
	},
};
const std::unordered_map<ZombieIndex, SDL_Rect> Zombie::ZOMBIE_SPRITE_CLIP_MAP = {
	{ ZombieIndex::Normal, { 16, 16, 96, 96 } },
	{ ZombieIndex::Bomber, { 16, 16, 96, 96 } },
	{ ZombieIndex::Lurker, { 32, 144, 80, 80 } },
	{ ZombieIndex::Tanker, { 16, 16, 96, 96 } },
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Zombie::Zombie() : GameObject("Zombie", Layer::Zombie) {

	lastGroanTick = 0.0f;
	groanDelay = Random::Float(GROAN_SOUND_DELAY_MIN, GROAN_SOUND_DELAY_MAX);

	zombieIndex = ZombieIndex::Normal;

	// Attribute
	zombieAttribute = new ZombieAttribute{
		.movementSpeed = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed,
		.health = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).health,
		.damage = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).damage,
		.exp = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).exp
	};
	// Calculation of zombie's attribute uses the following formula
	// y = bm(d * ln(x) + sqrt(m ^ x))
	// Where
	// b is the base attribute
	// m is the attribute's multiplier
	// d is the difficulty coefficient 
	// x is the wave
	zombieAttribute->health *= ZombieAttribute::HEALTH_MULTIPLIER
		* (
			WaveManager::Instance()->GetDifficulty() * std::logf(WaveManager::Instance()->GetCurrentWave()) +
			std::sqrtf(std::powf(ZombieAttribute::HEALTH_MULTIPLIER, WaveManager::Instance()->GetCurrentWave()))
			);
	zombieAttribute->damage *= ZombieAttribute::DAMAGE_MULTIPLIER
		* (
			WaveManager::Instance()->GetDifficulty() * std::logf(WaveManager::Instance()->GetCurrentWave()) +
			std::sqrtf(std::powf(ZombieAttribute::DAMAGE_MULTIPLIER, WaveManager::Instance()->GetCurrentWave()))
			);

	// Components
	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->drag = 10.0f;
	rigidBody->mass = 60.0f;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(zombieAttribute->health);
	humanoid->OnDeath = [this]() {
		GameManager::Instance()->ReportDead(this);
		};
	humanoid->OnDamaged = [this]() {
		MediaSFX audioIndex = static_cast<MediaSFX>(Random::Int(
			static_cast<int>(MediaSFX::ZombieHurt1), static_cast<int>(MediaSFX::ZombieHurt6)
		));
		AudioManager::Instance()->PlayOneShot(
			audioIndex, (transform->position - Player::Instance()->transform->position).Magnitude()
		);
		};

	Image* image = AddComponent<Image>();
	image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Entity_Zombie), false);
	image->showOnScreen = false;
	image->clip = ZOMBIE_SPRITE_CLIP_MAP.at(zombieIndex);

	transform->scale = Vector2(50.0f, 50.0f);

	// Fields

	healthBar = GameObject::Instantiate("Health Bar", Layer::Zombie);
	Image* healthBar_image = healthBar->AddComponent<Image>();
	healthBar_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_HealthBar), true);
	healthBar_image->imageFill = ImageFill::Horizontal;
	healthBar_image->fillAmount = 1.0f;
	healthBar_image->showOnScreen = false;
	healthBar->transform->scale *= HEALTH_BAR_SCALE;

	Render = [image, healthBar_image, humanoid, this, boxCollider]() {

		image->Render();

		// Render health bar
		healthBar_image->transform->position = transform->position + Vector2::up * HEALTH_BAR_VERTICAL_OFFSET;
		healthBar_image->fillAmount = humanoid->GetHealth() / humanoid->GetMaxHealth();
		healthBar_image->Render();

		boxCollider->Debug();

		};

}

Zombie::~Zombie() {

	GameObject::Destroy(healthBar);
	healthBar = nullptr;

	delete zombieAttribute;
	zombieAttribute = nullptr;

}

void Zombie::SetIndex(ZombieIndex initZombieIndex) {

	zombieIndex = initZombieIndex;

	zombieAttribute->movementSpeed = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed;
	zombieAttribute->health = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).health;
	zombieAttribute->damage = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).damage;
	zombieAttribute->exp = ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).exp;

	GetComponent<Image>()->clip = ZOMBIE_SPRITE_CLIP_MAP.at(zombieIndex);

}

void Zombie::Update() {

	if (!GameManager::Instance()->GameRunning())
		return;

	Vector2 forward = (Player::Instance()->transform->position - transform->position).Normalize();

	transform->Translate(
		forward * GameCore::DeltaTime() * ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed
	);

	// Calculate rotation
	GetComponent<Image>()->angle = Math::RadToDeg(forward.Angle());

	// Play sound
	if (GameCore::Time() >= lastGroanTick + groanDelay) {

		MediaSFX audioIndex = static_cast<MediaSFX>(Random::Int(
			static_cast<int>(MediaSFX::ZombieGroan1), static_cast<int>(MediaSFX::ZombieGroan4)
		));
		AudioManager::Instance()->PlayOneShot(
			audioIndex, (transform->position-Player::Instance()->transform->position).Magnitude()
		);

		lastGroanTick = GameCore::Time();
		groanDelay = Random::Float(GROAN_SOUND_DELAY_MIN, GROAN_SOUND_DELAY_MAX);

	}

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
			WaveManager::Instance()->GetDifficulty() * logf(WaveManager::Instance()->GetCurrentWave() +
				sqrtf(powf(ZombieAttribute::EXP_MULTIPLIER, WaveManager::Instance()->GetCurrentWave())))
			);

}