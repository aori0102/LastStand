#include <Projectile.h>
#include <Type.h>
#include <Game.h>

const float EXIST_TIME = 5.0f;

Projectile::Projectile(Vector2 initPosition, Vector2 initScale, Vector2 initDirection, float initVelocity, float initDamage) {

	Transform* transform = AddComponent<Transform>();
	transform->position = initPosition;
	transform->scale = initScale;

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

	Transform* transform = GetComponent<Transform>();

	Game::DrawRectangle(transform->position, transform->scale / 2.0f, false, true, Color::YELLOW);

	GetComponent<BoxCollider>()->Debug();

}

void Projectile::OnCollisionEnter(BoxCollider* collider) {

	Humanoid* humanoid = collider->GetComponent<Humanoid>();

	if (humanoid)
		humanoid->Damage(damage);

	GameObject::Destroy(this);

}