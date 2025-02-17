#include <Projectile.h>
#include <Type.h>
#include <Game.h>

const float EXIST_TIME = 5.0f;

Projectile::Projectile(Vector2 initPosition, Vector2 initScale, Vector2 initDirection, float initVelocity) {

	Transform* transform = AddComponent<Transform>();
	transform->position = initPosition;
	transform->scale = initScale;

	AddComponent<BoxCollider>();

	direction = initDirection;
	velocity = initVelocity;

	spawnTime = Game::GetTime();

}

void Projectile::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * Game::GetDeltaTime() * velocity, false);

	Render();

	if (Game::GetTime() >= spawnTime + EXIST_TIME)
		GameObject::Destroy(this);

}

void Projectile::Render() {

	Transform* transform = GetComponent<Transform>();

	Game::SetRenderDrawColor(Color::YELLOW);
	Game::DrawRectangle(transform->position, transform->scale / 2.0f, false);

	GetComponent<BoxCollider>()->Debug();

}

void Projectile::OnCollisionEnter(BoxCollider* collider) {

	Humanoid* humanoid = collider->GetOwner()->GetComponent<Humanoid>();

	if (humanoid)
		humanoid->Damage(10);

	GameObject::Destroy(this);

}