/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <Bullet.h>

#include <iomanip>
#include <sstream>

#include <GameCore.h>
#include <MediaManager.h>
#include <Player.h>
#include <Texture.h>
#include <Utils.h>
#include <Zombie.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const float Bullet::BULLET_EXIST_TIME = 5.0f;
const float Bullet::KNOCKBACK_FORCE = 37.0f;
const float Bullet::BULLET_VELOCITY = 4800.0f;
const float Bullet::DAMAGE_INDICATOR_SHOW_TIME = 0.7f;
const float Bullet::DAMAGE_INDICATOR_POP_UP_VELOCITY = 120.0f;
const float Bullet::DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION = 9.8f;
const float Bullet::DAMAGE_INDICATOR_ANGLE_OFFSET = 26.0f;
const int Bullet::DAMAGE_INDICATOR_FONT_SIZE = 18;
const int Bullet::DAMAGE_INDICATOR_DECIMAL = 2;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

Bullet::Bullet(Vector2 initPosition, Vector2 initDirection, float initDamage, bool isCrit) : GameObject("Bullet", Layer::Bullet) {

	// Components
	transform->position = initPosition;

	Image* bullet_image = AddComponent<Image>();
	bullet_image->LinkSprite(MediaManager::Instance()->GetObjectSprite(MediaObject::Misc_Bullet), false);
	bullet_image->showOnScreen = false;
	bullet_image->angle = Math::RadToDeg(initDirection.Angle());

	BoxCollider* boxCollider = AddComponent<BoxCollider>();
	boxCollider->ignoreLayerSet = { Layer::Player, Layer::Bullet };

	// Fields
	hitHumanoid = false;
	damage = initDamage;
	spawnTime = GameCore::Time();
	hitTime = 0.0f;

	indicatorOpacityFunction = [](float t) {
		Math::Clamp(t, 0.0f, 1.0f);
		return 1 - Math::Fade(t);
		};

	indicatorOffsetFunction = [this](float t) {
		Math::Clamp(t, 0.0f, 1.0f);
		float theta = std::abs(damageIndicatorPopUpDirection.Angle());
		return Vector2(
			DAMAGE_INDICATOR_POP_UP_VELOCITY * cosf(theta) * t,
			DAMAGE_INDICATOR_POP_UP_VELOCITY * sinf(theta) * t - 0.5f * DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION * t * t
		);
		};

	direction = initDirection;

	float angleInRad = std::abs(Math::DegToRad(DAMAGE_INDICATOR_ANGLE_OFFSET));
	float indicatorAngle = Random::Float(-angleInRad, angleInRad);
	damageIndicatorPopUpDirection = Vector2::up.Rotate(indicatorAngle);

	damageIndicator = new GameObject("Damage indicator", Layer::Bullet);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(DAMAGE_INDICATOR_DECIMAL) << initDamage;
	Text* damageIndicator_text = damageIndicator->AddComponent<Text>();
	damageIndicator_text->LoadText(
		ss.str(), isCrit ? Color::YELLOW : Color::RED, DAMAGE_INDICATOR_FONT_SIZE
	);
	damageIndicator_text->showOnScreen = false;
	damageIndicator->Render = [this, damageIndicator_text]() {
		if (!hitHumanoid)
			return;
		float time = (GameCore::Time() - hitTime) / DAMAGE_INDICATOR_SHOW_TIME;
		damageIndicator_text->transform->position = transform->position + indicatorOffsetFunction(time);
		damageIndicator_text->SetOpacity(indicatorOpacityFunction(time));

		damageIndicator_text->Render();
		};
	damageIndicator->Disable();

	Render = [this, bullet_image]() {
		if (!hitHumanoid)
			bullet_image->Render();
		};

}

void Bullet::Update() {

	if (hitHumanoid) {

		if (GameCore::Time() >= hitTime + DAMAGE_INDICATOR_SHOW_TIME)
			GameObject::Destroy(this);

	} else {

		transform->Translate(direction.Normalize() * GameCore::DeltaTime() * BULLET_VELOCITY, false);

		if (GameCore::Time() >= spawnTime + BULLET_EXIST_TIME)
			GameObject::Destroy(this);

	}

}

void Bullet::OnCollisionEnter(BoxCollider* collider) {

	if (hitHumanoid)
		return;

	Humanoid* humanoid = nullptr;
	if (collider->TryGetComponent<Humanoid>(humanoid))
		humanoid->Damage(damage);

	RigidBody* rigidBody = nullptr;
	if (collider->TryGetComponent<RigidBody>(rigidBody))
		rigidBody->AddForce(direction.Normalize() * KNOCKBACK_FORCE);

	if (!humanoid) // Hit anything but humanoid, destroy the bullet
		GameObject::Destroy(this);
	else {			// Otherwise render the damage

		GetComponent<BoxCollider>()->Disable();
		hitHumanoid = true;
		damageIndicator->transform->position = transform->position;
		damageIndicator->Enable();
		hitTime = GameCore::Time();

	}

}

void Bullet::OnDestroy() {

	GameObject::Destroy(damageIndicator);

}