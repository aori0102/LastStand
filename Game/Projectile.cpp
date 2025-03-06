#include <Projectile.h>
#include <Type.h>
#include <Game.h>
#include <Texture.h>

const float EXIST_TIME = 5.0f;
const string BULLET_PATH = "./Asset/Bullet.png";

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

	Humanoid* humanoid = collider->GetComponent<Humanoid>();

	std::cout << Game::Time() << std::endl;
	std::cout << "Hit " << collider->Owner()->name << " (" << collider << " | " << collider->Owner() << ")" << std::endl;

	if (humanoid)
		humanoid->Damage(damage);

	GameObject::Destroy(this);

}