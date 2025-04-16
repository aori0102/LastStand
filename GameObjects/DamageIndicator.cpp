/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<
/// ---------------------------------------------------------------
///						     AUTHORED: アオリ
/// ---------------------------------------------------------------
/// >>> >>> >>> >>> >>> >>> >>> ------- <<< <<< <<< <<< <<< <<< <<<

#include <DamageIndicator.h>

#include <iomanip>
#include <sstream>

#include <GameCore.h>
#include <Texture.h>

/// ----------------------------------
/// STATIC FIELDS
/// ----------------------------------

const int DamageIndicator::DAMAGE_INDICATOR_FONT_SIZE = 18;
const int DamageIndicator::DAMAGE_INDICATOR_DECIMAL = 2;
const float DamageIndicator::DAMAGE_INDICATOR_SHOW_TIME = 0.7f;
const float DamageIndicator::DAMAGE_INDICATOR_POP_UP_VELOCITY = 120.0f;
const float DamageIndicator::DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION = 9.8f;

/// ----------------------------------
/// METHOD DEFINITIONS
/// ----------------------------------

void DamageIndicator::InitializeComponents() {

	Text* text = AddComponent<Text>();
	text->showOnScreen = false;
	Render = [this]() {
		RenderUI();
		};

	Disable();

}

void DamageIndicator::RenderUI() {

	float time = (GameCore::Time() - initiateTime) / DAMAGE_INDICATOR_SHOW_TIME;
	transform->position = position+ GetOffset(time);

	Text* text = GetComponent<Text>();
	text->SetOpacity(GetOpacity(time));
	text->Render();

}

float DamageIndicator::GetOpacity(float time) {

	Math::Clamp(time, 0.0f, 1.0f);
	return 1.0f - Math::Fade(time);

}

Vector2 DamageIndicator::GetOffset(float time) {

	Math::Clamp(time, 0.0f, 1.0f);
	float theta = std::abs(direction.Angle());
	return Vector2(
		DAMAGE_INDICATOR_POP_UP_VELOCITY * cosf(theta) * time,
		DAMAGE_INDICATOR_POP_UP_VELOCITY * sinf(theta) * time - 0.5f * DAMAGE_INDICATOR_GRAVITAIONAL_DECELERATION * time * time
	);

}

DamageIndicator::DamageIndicator() {

	initiateTime = 0.0f;
	direction = Vector2::zero;

	InitializeComponents();

}

void DamageIndicator::SetDamage(float damage, bool isCrit) {

	std::stringstream ss;
	ss << std::fixed << std::setprecision(DAMAGE_INDICATOR_DECIMAL) << damage;

	GetComponent<Text>()->LoadText(ss.str(), isCrit ? Color::YELLOW : Color::RED, DAMAGE_INDICATOR_FONT_SIZE);

}

void DamageIndicator::Initiate(Vector2 initPosition, Vector2 initDirection) {

	position = initPosition;
	direction = initDirection;

	initiateTime = GameCore::Time();

	Enable();

}

void DamageIndicator::Update() {

	if (GameCore::Time() >= initiateTime + DAMAGE_INDICATOR_SHOW_TIME)
		GameObject::Destroy(this);

}