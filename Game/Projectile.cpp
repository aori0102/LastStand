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

	spawnTime = Game::time;

}

void Projectile::Update() {

	GetComponent<Transform>()->Translate(direction.Normalize() * Game::deltaTime * velocity, false);

	Render();

	if (Game::time >= spawnTime + EXIST_TIME)
		GameObject::Destroy(this);

}

void Projectile::Render() {

	Transform* transform = GetComponent<Transform>();

	Game::SetRenderDrawColor(Color::WHITE);
	SDL_FRect quad = { transform->position.x, transform->position.y, transform->scale.x, transform->scale.y };

	SDL_RenderFillRectF(Game::gRenderer, &quad);

	GetComponent<BoxCollider>()->Debug();

}

void Projectile::OnCollisionEnter(BoxCollider* collider) {

	Humanoid* humanoid = collider->GetOwner()->GetComponent<Humanoid>();

	if (humanoid)
		humanoid->Damage(10);

	GameObject::Destroy(this);

}