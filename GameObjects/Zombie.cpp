﻿/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
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
const float ZombieAttribute::MONEY_MULTIPLIER = 1.02f;
const float Zombie::KNOCKBACK_FORCE = 50.0f;
const float Zombie::HEALTH_BAR_VERTICAL_OFFSET = 50.0f;
const float Zombie::HEALTH_BAR_SCALE = 0.4f;
const float Zombie::GROAN_SOUND_DELAY_MIN = 4.7f;
const float Zombie::GROAN_SOUND_DELAY_MAX = 9.9f;
const float Zombie::HURT_VISUAL_DISPLAY_TIME = 0.14f;
const std::unordered_map<ZombieIndex, ZombieAttribute> Zombie::ZOMBIE_BASE_ATTRIBUTE_MAP = {
	{ ZombieIndex::Normal, ZombieAttribute{
		.movementSpeed = 60.0f,
		.health = 32.0f,
		.damage = 6.0f,
		.scale = 56.0f,
		.mass = 60.0f,
		.exp = 3,
		.money = 13,
		}
	},
	{ ZombieIndex::Lurker, ZombieAttribute{
		.movementSpeed = 134.0f,
		.health = 21.0f,
		.damage = 3.0f,
		.scale = 42.0f,
		.mass = 44.0f,
		.exp = 7,
		.money = 17,
		}
	},
	{ ZombieIndex::Tanker, ZombieAttribute{
		.movementSpeed = 30.0f,
		.health = 148.0f,
		.damage = 3.0f,
		.scale = 88.0f,
		.mass = 214.0f,
		.exp = 9,
		.money = 22,
		}
	},
};
const std::unordered_map<ZombieIndex, SDL_Rect> Zombie::ZOMBIE_SPRITE_CLIP_MAP = {
	{ ZombieIndex::Normal, { 16, 16, 96, 96 } },
	{ ZombieIndex::Lurker, { 32, 144, 80, 80 } },
	{ ZombieIndex::Tanker, { 160, 16, 128, 128 } },
};

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Zombie::InitializeData() {

	displayHurt = false;
	lastGroanTick = 0.0f;
	groanDelay = Random::Float(GROAN_SOUND_DELAY_MIN, GROAN_SOUND_DELAY_MAX);

	wanderTarget = Vector2::zero;

	zombieIndex = static_cast<ZombieIndex>(Random::Int(static_cast<int>(ZombieIndex::Normal),static_cast<int>(ZombieIndex::Tanker)));

	// Attribute
	zombieAttribute = new ZombieAttribute(ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex));

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
	zombieAttribute->exp = static_cast<int>(zombieAttribute->exp * ZombieAttribute::EXP_MULTIPLIER
		* (
			WaveManager::Instance()->GetDifficulty() * logf(WaveManager::Instance()->GetCurrentWave() +
				sqrtf(powf(ZombieAttribute::EXP_MULTIPLIER, WaveManager::Instance()->GetCurrentWave())))
			));
	zombieAttribute->money = static_cast<int>(zombieAttribute->money * ZombieAttribute::MONEY_MULTIPLIER
		* (
			WaveManager::Instance()->GetDifficulty() * logf(WaveManager::Instance()->GetCurrentWave() +
				sqrtf(powf(ZombieAttribute::MONEY_MULTIPLIER, WaveManager::Instance()->GetCurrentWave())))
			));

}

void Zombie::InitializeComponents() {

	RigidBody* rigidBody = AddComponent<RigidBody>();
	rigidBody->drag = 10.0f;
	rigidBody->mass = zombieAttribute->mass;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();

	Humanoid* humanoid = AddComponent<Humanoid>();
	humanoid->SetHealth(zombieAttribute->health);
	humanoid->SetMaxHealth(zombieAttribute->health);
	humanoid->OnDeath = [this]() {
		GameManager::Instance()->ReportDead(this);
		};
	humanoid->OnDamaged = [this]() {
		displayHurt = true;
		lastHurtTick = GameCore::Time();
		GetComponent<Image>()->SetColorModulo(Color::RED);
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

	transform->scale = Vector2(zombieAttribute->scale, zombieAttribute->scale);

	healthBar = GameObject::Instantiate("Zombie Health Bar", Layer::Zombie);
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

		//boxCollider->Debug();

		};

}

void Zombie::FollowPlayer() {

	Vector2 forward = (Player::Instance()->transform->position - transform->position).Normalize();

	transform->Translate(
		forward.Normalize() * GameCore::DeltaTime() * ZOMBIE_BASE_ATTRIBUTE_MAP.at(zombieIndex).movementSpeed
	);

	// Calculate rotation
	GetComponent<Image>()->angle = Math::RadToDeg(forward.Angle());

	// Play sound
	if (GameCore::Time() >= lastGroanTick + groanDelay) {

		MediaSFX audioIndex = static_cast<MediaSFX>(Random::Int(
			static_cast<int>(MediaSFX::ZombieGroan1), static_cast<int>(MediaSFX::ZombieGroan4)
		));
		AudioManager::Instance()->PlayOneShot(
			audioIndex, (transform->position - Player::Instance()->transform->position).Magnitude()
		);

		lastGroanTick = GameCore::Time();
		groanDelay = Random::Float(GROAN_SOUND_DELAY_MIN, GROAN_SOUND_DELAY_MAX);

	}

}

Zombie::Zombie() {

	InitializeData();
	InitializeComponents();

}

Zombie::~Zombie() {

	GameObject::Destroy(healthBar);
	healthBar = nullptr;

	delete zombieAttribute;
	zombieAttribute = nullptr;

}

void Zombie::Update() {

	if (!GameManager::Instance()->GameRunning())
		return;

	FollowPlayer();

	if (displayHurt && GameCore::Time() >= lastHurtTick + HURT_VISUAL_DISPLAY_TIME) {

		displayHurt = false;
		GetComponent<Image>()->SetColorModulo(Color::WHITE);

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

int Zombie::GetExp() const { return zombieAttribute->exp; }

int Zombie::GetMoney() const { return zombieAttribute->money; }