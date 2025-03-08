#include <Projectile.h>
#include <Type.h>
#include <Game.h>
#include <Texture.h>

const float EXIST_TIME = 5.0f;
const std::string BULLET_PATH = "./Asset/Bullet.png";
const float Projectile::KNOCKBACK_FORCE = 37.0f;

Projectile::Projectile(GameObject* initShooter, Vector2 initPosition, Vector2 initDirection, float initVelocity, float initDamage) : GameObject("Projectile", Layer::Projectile) {

	Transform* transform = AddComponent<Transform>();
	transform->position = initPosition;
	
	shooter = initShooter;

	Image* image = AddComponent<Image>();
	image->LoadImage(BULLET_PATH);
	image->showOnScreen = false;
	image->angle = Math::RadToDeg(initDirection.Angle());

	transform->scale *= 2.0f;

	BoxCollider* boxCollider = AddComponent<BoxCollider>();
	boxCollider->ignoreLayerSet.insert(Layer::Player);

	direction = initDirection;
	velocity = initVelocity;
	damage = initDamage;

	spawnTime = Game::Time();

	Render = [this]() {
		GetComponent<Image>()->Render();
		};

}

void Projectile::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * Game::DeltaTime() * velocity, false);

	if (Game::Time() >= spawnTime + EXIST_TIME)
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