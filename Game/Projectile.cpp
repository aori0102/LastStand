#include <Projectile.h>
#include <Type.h>
#include <Game.h>
#include <Texture.h>

const float EXIST_TIME = 5.0f;
const string BULLET_PATH = "./Asset/Bullet.png";

Projectile::Projectile(Vector2 initPosition, Vector2 initDirection, float initVelocity, float initDamage) {

	Transform* transform = AddComponent<Transform>();
	transform->position = initPosition;

	Image* image = AddComponent<Image>();
	image->LoadImage(BULLET_PATH);
	image->showOnScreen = false;
	image->angle = -Math::RadToDeg(initDirection.Angle());

	transform->scale *= 2.0f;

	AddComponent<BoxCollider>();

	direction = initDirection;
	velocity = initVelocity;
	damage = initDamage;

	spawnTime = Game::Time();

}

void Projectile::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * Game::DeltaTime() * velocity, false);

	Render();

	if (Game::Time() >= spawnTime + EXIST_TIME)
		GameObject::Destroy(this);

}

void Projectile::Render() {

	GetComponent<Image>()->Render();

}

void Projectile::OnCollisionEnter(BoxCollider* collider) {

	Humanoid* humanoid = collider->GetComponent<Humanoid>();

	if (humanoid)
		humanoid->Damage(damage);

	GameObject::Destroy(this);

}