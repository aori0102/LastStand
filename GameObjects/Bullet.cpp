#include <Bullet.h>
#include <Type.h>
#include <GameCore.h>
#include <Texture.h>
#include <MediaManager.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float EXIST_TIME = 5.0f;
const float Bullet::KNOCKBACK_FORCE = 37.0f;
const float Bullet::BULLET_VELOCITY = 4800.0f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Bullet::Bullet(GameObject* initShooter, Vector2 initPosition, Vector2 initDirection, float initDamage) : GameObject("Bullet", Layer::Bullet) {

	Transform* transform = AddComponent<Transform>();
	transform->position = initPosition;

	shooter = initShooter;

	Image* image = AddComponent<Image>();
	image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Bullet), false);
	image->showOnScreen = false;
	image->angle = Math::RadToDeg(initDirection.Angle());

	transform->scale *= 2.0f;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();
	boxCollider->ignoreLayerSet.insert(Layer::Player);

	direction = initDirection;
	damage = initDamage;

	spawnTime = GameCore::Time();

	Render = [this]() {
		GetComponent<Image>()->Render();
		};

}

void Bullet::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * GameCore::DeltaTime() * BULLET_VELOCITY, false);

	if (GameCore::Time() >= spawnTime + EXIST_TIME)
		GameObject::Destroy(this);

}

void Bullet::OnCollisionEnter(BoxCollider* collider) {

	if (collider->Owner() == shooter || collider->Owner()->GetLayer() == Layer::Bullet)
		return;

	Humanoid* humanoid = nullptr;
	if (collider->TryGetComponent<Humanoid>(humanoid))
		humanoid->Damage(damage);

	RigidBody* rigidBody = nullptr;
	if (collider->TryGetComponent<RigidBody>(rigidBody))
		rigidBody->AddForce(direction.Normalize() * KNOCKBACK_FORCE);

	GameObject::Destroy(this);

}