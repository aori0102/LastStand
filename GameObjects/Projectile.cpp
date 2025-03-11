#include <Projectile.h>
#include <Type.h>
#include <GameCore.h>
#include <Texture.h>
#include <MediaManager.h>

const float EXIST_TIME = 5.0f;
const float Projectile::KNOCKBACK_FORCE = 37.0f;

Projectile::Projectile(GameObject* initShooter, Vector2 initPosition, Vector2 initDirection, float initVelocity, float initDamage) : GameObject("Projectile", Layer::Projectile) {

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
	velocity = initVelocity;
	damage = initDamage;

	spawnTime = GameCore::Time();

	Render = [this]() {
		GetComponent<Image>()->Render();
		};

}

void Projectile::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * GameCore::DeltaTime() * velocity, false);

	if (GameCore::Time() >= spawnTime + EXIST_TIME)
		GameObject::Destroy(this);

}

void Projectile::OnCollisionEnter(BoxCollider* collider) {

	if (collider->Owner() == shooter)
		return;

	Humanoid* humanoid = nullptr;
	if (collider->TryGetComponent<Humanoid>(humanoid))
		humanoid->Damage(damage);

	RigidBody* rigidBody = nullptr;
	if (collider->TryGetComponent<RigidBody>(rigidBody))
		rigidBody->AddForce(direction.Normalize() * KNOCKBACK_FORCE);

	GameObject::Destroy(this);

}