/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Bullet.h>

#include <iomanip>
#include <sstream>

#include <BoxCollider.h>
#include <DamageIndicator.h>
#include <GameCore.h>
#include <GameManager.h>
#include <Humanoid.h>
#include <MediaManager.h>
#include <Player.h>
#include <PlayerStatistic.h>
#include <RigidBody.h>
#include <Texture.h>
#include <Transform.h>
#include <Utils.h>
#include <Zombie.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float Bullet::BULLET_EXIST_TIME = 5.0f;
const float Bullet::KNOCKBACK_FORCE = 37.0f;
const float Bullet::BULLET_VELOCITY = 4800.0f;
const float Bullet::DAMAGE_INDICATOR_ANGLE_OFFSET = 26.0f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void Bullet::OnHumanoidHit(Humanoid* target) {

	// Damage humanoid
	target->Damage(damage);
	PlayerStatistic::Instance()->AddDamage(damage);

	// Knockback
	RigidBody* rigidBody = nullptr;
	if (target->TryGetComponent<RigidBody>(rigidBody))
		rigidBody->AddForce(direction.Normalize() * KNOCKBACK_FORCE);

	// Show damage
	DamageIndicator* indicator = GameObject::Instantiate<DamageIndicator>("Damage Indicator", Layer::Bullet);

	indicator->SetDamage(damage, isCrit);

	float angleInRad = std::abs(Math::DegToRad(DAMAGE_INDICATOR_ANGLE_OFFSET));
	float indicatorAngle = Random::Float(-angleInRad, angleInRad);
	indicator->Initiate(transform->position, Vector2::up.Rotate(indicatorAngle));

}

void Bullet::InitializeComponents() {

	Image* bullet_image = AddComponent<Image>();
	bullet_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Bullet), false);
	bullet_image->showOnScreen = false;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();
	boxCollider->ignoreLayerSet = { Layer::Player, Layer::Bullet };

	Render = [bullet_image]() {
		bullet_image->Render();
		};

}

Bullet::Bullet() {

	isCrit = false;
	damage = 0.0f;
	spawnTime = GameCore::Time();
	direction = Vector2::zero;

	InitializeComponents();

}

void Bullet::Update() {

	if (!GameManager::Instance()->GameRunning())
		return;

	transform->Translate(direction.Normalize() * GameCore::DeltaTime() * BULLET_VELOCITY, false);

	if (GameCore::Time() >= spawnTime + BULLET_EXIST_TIME)
		GameObject::Destroy(this);

}

void Bullet::SetUpBullet(Vector2 initPosition, Vector2 initDirection, float initDamage, bool initIsCrit) {

	isCrit = initIsCrit;
	transform->position = initPosition;

	direction = initDirection;

	damage = initDamage;
	GetComponent<Image>()->angle = Math::RadToDeg(initDirection.Angle());

}

void Bullet::OnCollisionEnter(BoxCollider* collider) {

	Humanoid* humanoid = nullptr;
	if (collider->TryGetComponent<Humanoid>(humanoid))
		OnHumanoidHit(humanoid);

	GameObject::Destroy(this);

}